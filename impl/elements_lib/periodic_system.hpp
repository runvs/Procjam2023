#ifndef PERIODIC_SYSTEM_HPP
#define PERIODIC_SYSTEM_HPP

#include <elements_lib/element.hpp>
#include <game_object.hpp>
#include <vector>

enum class ColorByE {
    // clang-format off
    None,
    Density,
    ThermalMeltingPoint,
    ThermalBoilingPoint,
    ReactivityPH,
    ReactivityElectronegativity,
    ThermalConductivity,
    ThermalCapacity,
    ElectricalConductivity,
    ElectricalCapacity,
    MagneticSusceptibility
    // clang-format on
};

class PeriodicSystem : public jt::GameObject {
public:
    void add(Element const& element);

    int getCurrentPeriod() const;
    int getCurrentGroup() const;

private:
    int m_period_current { 1 };
    int m_group_current { 1 };
    int m_elements_per_period_current { 2 };
    int m_elements_per_period_max { 16 };

    mutable std::string jsonText;
    mutable bool m_json_open { false };

    mutable std::vector<Element> m_elements;

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    Element* getElement(int group, int period) const;

    mutable ColorByE m_colorBy { ColorByE::None };
    mutable float m_colorMinValue { 0.0f };
    mutable float m_colorMaxValue { 1.0f };
    void colorButtons(Element const* e) const;
    void switchToColor(ColorByE type) const;
};

#endif // PERIODIC_SYSTEM_HPP
