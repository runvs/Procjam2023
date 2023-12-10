#include "state_game.hpp"
#include <box2dwrapper/box2d_world_impl.hpp>
#include <elements_lib/element_factory.hpp>
#include <game_interface.hpp>
#include <game_properties.hpp>
#include <hud/hud.hpp>
#include <shape.hpp>
#include <imgui.h>

void StateGame::rollNewElements()
{
    if (m_periodicSystem) {
        m_periodicSystem->kill();
    }
    m_periodicSystem = std::make_shared<PeriodicSystem>();
    ElementFactory factory {};
    for (auto i = 0u; i != 100; ++i) {
        auto e = factory.makeRandomElement(*m_periodicSystem);
        m_periodicSystem->add(e);
    }
    add(m_periodicSystem);
}

void StateGame::onCreate()
{
    float const w = static_cast<float>(GP::GetWindowSize().x);
    float const h = static_cast<float>(GP::GetWindowSize().y);

    using jt::Shape;

    m_background = std::make_shared<Shape>();
    m_background->makeRect({ w, h }, textureManager());
    m_background->setColor(GP::PaletteBackground());
    m_background->setIgnoreCamMovement(true);
    m_background->update(0.0f);

    rollNewElements();

    // StateGame will call drawObjects itself.
    setAutoDraw(false);
}

void StateGame::onEnter() { }

void StateGame::onUpdate(float const elapsed)
{
    m_background->update(elapsed);
    if (m_rollNew) {
        m_rollNew = false;
        rollNewElements();
    }
}

void StateGame::onDraw() const
{
    ImGui::Begin("Elements");

    if (ImGui::Button("Roll new elements")) {
        m_rollNew = true;
    }
    ImGui::Separator();
    ImGui::End();

    m_background->draw(renderTarget());
    drawObjects();
}

std::string StateGame::getName() const { return "State Game"; }
