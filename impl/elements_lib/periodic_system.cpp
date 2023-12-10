#include "periodic_system.hpp"
#include <imgui.h>
#include <iostream>

namespace {
std::map<ColorByE, std::function<float(Element const&)>> createElementLookups()
{
    std::map<ColorByE, std::function<float(Element const&)>> lookups;
    // clang-format off
    lookups[ColorByE::None] = [](Element const& /*e*/) { return 0.5f; };
    lookups[ColorByE::Density] = [](Element const& e) { return e.density; };
    lookups[ColorByE::ThermalMeltingPoint]
        = [](Element const& e) { return e.thermal_melting_point; };
    lookups[ColorByE::ThermalBoilingPoint]
        = [](Element const& e) { return e.thermal_boiling_point; };
    lookups[ColorByE::ReactivityPH]
            = [](Element const& e) { return e.reactivity_pH; };
    lookups[ColorByE::ReactivityElectronegativity]
        = [](Element const& e) { return e.reactivity_electronegativity; };
    lookups[ColorByE::ThermalConductivity]
        = [](Element const& e) { return e.thermal_conductivity; };
    lookups[ColorByE::ThermalCapacity]
        = [](Element const& e) { return e.thermal_capacity; };
    lookups[ColorByE::ElectricalConductivity]
        = [](Element const& e) { return e.electrical_conductivity; };
    lookups[ColorByE::ElectricalCapacity]
        = [](Element const& e) { return e.electrical_capacity; };
    lookups[ColorByE::MagneticSusceptibility]
        = [](Element const& e) { return e.magnetic_susceptibility; };
    // clang-format on
    return lookups;
}

} // namespace

void PeriodicSystem::add(Element const& element)
{
    m_group_current++;
    if (m_group_current > m_elements_per_period_current) {
        m_period_current += 1;
        m_group_current = 1;
        m_elements_per_period_current *= 2;
        if (m_elements_per_period_current >= 16) {
            m_elements_per_period_current = 16;
        }
    }
    m_elements.push_back(element);
}

int PeriodicSystem::getCurrentPeriod() const { return m_period_current; }

int PeriodicSystem::getCurrentGroup() const { return m_group_current; }

void PeriodicSystem::doCreate() { }

void PeriodicSystem::doUpdate(float const elapsed) { }

void drawTooltip(Element const* e)
{
    ImGui::Text("Name: '%s' (%s)", e->name.c_str(), e->symbol.c_str());

    ImGui::Text(" ");
    ImGui::Text("atomic number: %i", e->atomic_number);
    ImGui::Text("group: %i", e->group);
    ImGui::Text("period: %i", e->period);

    ImGui::Text(" ");
    ImGui::Text("density: %.2f", e->density);

    ImGui::Text(" ");
    ImGui::Text("melting point: %.2f", e->thermal_melting_point);
    ImGui::Text("boiling point: %.2f", e->thermal_boiling_point);

    ImGui::Text(" ");
    ImGui::Text("pH: %2f", e->reactivity_pH);
    ImGui::Text("electronegativity: %2f", e->reactivity_electronegativity);

    ImGui::Text(" ");
    ImGui::Text("thermal conductivity: %2f", e->thermal_conductivity);
    ImGui::Text("thermal capacity: %2f", e->thermal_capacity);

    ImGui::Text(" ");
    ImGui::Text("electrical conductivity: %2f", e->electrical_conductivity);
    ImGui::Text("electrical capacity: %2f", e->electrical_capacity);
    ImGui::Text("magnetic susceptibility: %2f", e->magnetic_susceptibility);
}

void PeriodicSystem::colorButtons(Element const* e) const
{
    static auto const lookups = createElementLookups();

    if (m_colorBy == ColorByE::None) {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 { 0.25f, 0.25f, 0.25f, 255 });
        return;
    }

    auto const fn = lookups.at(m_colorBy);
    auto const elementValue = fn(*e);
    auto const v = (elementValue - m_colorMinValue) / (m_colorMaxValue - m_colorMinValue);
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 { v, 0.25f, 0.25f, 255 });
}

void PeriodicSystem::switchToColor(ColorByE type) const
{
    m_colorBy = type;
    m_colorMaxValue = 0.0f;
    m_colorMinValue = 0.0f;
    static auto const lookups = createElementLookups();
    auto const& fn = lookups.at(type);

    for (auto& e : m_elements) {
        auto const v = fn(e);
        if (v >= m_colorMaxValue) {
            m_colorMaxValue = v;
        }
        if (v <= m_colorMinValue) {
            m_colorMinValue = v;
        }
    }
}

void PeriodicSystem::doDraw() const
{
    ImGui::Begin("Elements");

    ImGui::Text("Color By");
    std::map<ColorByE, std::string> buttons {
        // clang-format off
        {ColorByE::None, "None"},
        {ColorByE::Density, "Density"},
        {ColorByE::ThermalMeltingPoint, "Melting Point"},
        {ColorByE::ThermalBoilingPoint, "Boiling Point"},
        {ColorByE::ReactivityPH, "pH"},
        {ColorByE::ReactivityElectronegativity, "Electronegativity"},
        {ColorByE::ThermalConductivity, "Th. Conductivity"},
        {ColorByE::ThermalCapacity, "Th. Capacity"},
        {ColorByE::ElectricalConductivity, "El. Conductivity"},
        {ColorByE::ElectricalCapacity, "El. Capacity"},
        {ColorByE::MagneticSusceptibility, "Mag. Susceptibility"}
        // clang-format on
    };
    std::size_t i = 0;
    for (auto const& kvp : buttons) {
        if (ImGui::Button(kvp.second.c_str())) {
            switchToColor(kvp.first);
        }
        ++i;
        if (i != buttons.size()) {
            ImGui::SameLine();
        }
    }
    ImGui::Separator();
    if (ImGui::BeginTable("table1", m_elements_per_period_max)) {
        for (int period = 1; period < m_period_current; period++) {
            ImGui::TableNextRow();
            for (int group = 1; group < m_elements_per_period_max; group++) {
                ImGui::TableSetColumnIndex(group);
                Element* e = getElement(group, period);
                if (e) {
                    colorButtons(e);
                    ImGui::Button(e->symbol.c_str(), ImVec2 { 48, 24 });
                    ImGui::PopStyleColor();
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        drawTooltip(e);
                        ImGui::EndTooltip();
                    }
                }
            }
        }
        ImGui::EndTable();
    }

    ImGui::Separator();
    if (ImGui::Button("to json")) {
        m_json_open = true;
        nlohmann::json j = m_elements;
        jsonText = j.dump(2);
    }
    ImGui::End();
    if (m_json_open) {
        ImGui::Begin("json", &m_json_open);

        if (ImGui::Button("print to js console (press F12 to open)")) {
            std::cout << std::endl << jsonText << std::endl;
        }

        auto start = jsonText.c_str();
        auto end = jsonText.c_str() + jsonText.size();
        ImGui::TextUnformatted(start, end);
        ImGui::End();
    }
}

Element* PeriodicSystem::getElement(int group, int period) const
{
    for (auto& e : m_elements) {
        if (e.group == group && e.period == period) {
            return &e;
        }
    }
    return nullptr;
}
