#ifndef GAME_STATE_GAME_HPP
#define GAME_STATE_GAME_HPP

#include "elements_lib/periodic_system.hpp"
#include <box2dwrapper/box2d_world_interface.hpp>
#include <game_state.hpp>
#include <player/player.hpp>
#include <memory>
#include <vector>

// fwd decls
namespace jt {
class Shape;
class Sprite;
class Vignette;
} // namespace jt

class Hud;

class StateGame : public jt::GameState {
public:
    std::string getName() const override;

private:
    std::shared_ptr<jt::Shape> m_background;
    std::shared_ptr<PeriodicSystem> m_periodicSystem;
    mutable bool m_rollNew { false };

    void rollNewElements();
    void onCreate() override;
    void onEnter() override;
    void onUpdate(float const elapsed) override;
    void onDraw() const override;
};

#endif
