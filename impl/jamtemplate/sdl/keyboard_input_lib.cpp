﻿#include "keyboard_input_lib.hpp"
#include <sdl_2_include.hpp>
#include <cstdint>

namespace jt {

namespace {

std::uint8_t toLib(jt::KeyCode k) noexcept
{
    switch (k) {
    case KeyCode::A:
        return SDL_SCANCODE_A;
    case KeyCode::B:
        return SDL_SCANCODE_B;
    case KeyCode::C:
        return SDL_SCANCODE_C;
    case KeyCode::D:
        return SDL_SCANCODE_D;
    case KeyCode::E:
        return SDL_SCANCODE_E;
    case KeyCode::F:
        return SDL_SCANCODE_F;
    case KeyCode::G:
        return SDL_SCANCODE_G;
    case KeyCode::H:
        return SDL_SCANCODE_H;
    case KeyCode::I:
        return SDL_SCANCODE_I;
    case KeyCode::J:
        return SDL_SCANCODE_J;
    case KeyCode::K:
        return SDL_SCANCODE_K;
    case KeyCode::L:
        return SDL_SCANCODE_L;
    case KeyCode::M:
        return SDL_SCANCODE_M;
    case KeyCode::N:
        return SDL_SCANCODE_N;
    case KeyCode::O:
        return SDL_SCANCODE_O;
    case KeyCode::P:
        return SDL_SCANCODE_P;
    case KeyCode::Q:
        return SDL_SCANCODE_Q;
    case KeyCode::R:
        return SDL_SCANCODE_R;
    case KeyCode::S:
        return SDL_SCANCODE_S;
    case KeyCode::T:
        return SDL_SCANCODE_T;
    case KeyCode::U:
        return SDL_SCANCODE_U;
    case KeyCode::V:
        return SDL_SCANCODE_V;
    case KeyCode::W:
        return SDL_SCANCODE_W;
    case KeyCode::X:
        return SDL_SCANCODE_X;
    case KeyCode::Y:
        return SDL_SCANCODE_Y;
    case KeyCode::Z:
        return SDL_SCANCODE_Z;
    case KeyCode::Num0:
        return SDL_SCANCODE_0;
    case KeyCode::Num1:
        return SDL_SCANCODE_1;
    case KeyCode::Num2:
        return SDL_SCANCODE_2;
    case KeyCode::Num3:
        return SDL_SCANCODE_3;
    case KeyCode::Num4:
        return SDL_SCANCODE_4;
    case KeyCode::Num5:
        return SDL_SCANCODE_5;
    case KeyCode::Num6:
        return SDL_SCANCODE_6;
    case KeyCode::Num7:
        return SDL_SCANCODE_7;
    case KeyCode::Num8:
        return SDL_SCANCODE_8;
    case KeyCode::Num9:
        return SDL_SCANCODE_9;
    case KeyCode::Escape:
        return SDL_SCANCODE_ESCAPE;
    case KeyCode::LControl:
        return SDL_SCANCODE_LCTRL;
    case KeyCode::LShift:
        return SDL_SCANCODE_LSHIFT;
    case KeyCode::LAlt:
        return SDL_SCANCODE_LALT;
    case KeyCode::LSystem:
        return SDL_SCANCODE_LCTRL;
    case KeyCode::RControl:
        return SDL_SCANCODE_RCTRL;
    case KeyCode::RShift:
        return SDL_SCANCODE_RSHIFT;
    case KeyCode::RAlt:
        return SDL_SCANCODE_RALT;
    case KeyCode::RSystem:
        return SDL_SCANCODE_RCTRL;
    case KeyCode::Menu:
        return SDL_SCANCODE_MENU;
    case KeyCode::LBracket:
        return SDL_SCANCODE_LEFTBRACKET;
    case KeyCode::RBracket:
        return SDL_SCANCODE_RIGHTBRACKET;
    case KeyCode::Semicolon:
        return SDL_SCANCODE_SEMICOLON;
    case KeyCode::Comma:
        return SDL_SCANCODE_COMMA;
    case KeyCode::Period:
        return SDL_SCANCODE_PERIOD;
    case KeyCode::Quote:
        return SDL_SCANCODE_APOSTROPHE;
    case KeyCode::Slash:
        return SDL_SCANCODE_SLASH;
    case KeyCode::Backslash:
        return SDL_SCANCODE_BACKSLASH;
    case KeyCode::Tilde:
        return SDL_SCANCODE_GRAVE;
    case KeyCode::Equal:
        return SDL_SCANCODE_EQUALS;
    case KeyCode::Space:
        return SDL_SCANCODE_SPACE;
    case KeyCode::Enter:
        return SDL_SCANCODE_RETURN;
    case KeyCode::Backspace:
        return SDL_SCANCODE_BACKSPACE;
    case KeyCode::Tab:
        return SDL_SCANCODE_TAB;
    case KeyCode::PageUp:
        return SDL_SCANCODE_PAGEUP;
    case KeyCode::PageDown:
        return SDL_SCANCODE_PAGEDOWN;
    case KeyCode::End:
        return SDL_SCANCODE_END;
    case KeyCode::Home:
        return SDL_SCANCODE_HOME;
    case KeyCode::Insert:
        return SDL_SCANCODE_INSERT;
    case KeyCode::Delete:
        return SDL_SCANCODE_DELETE;
    // case KeyCode::Add:
    case KeyCode::Subtract:
        return SDL_SCANCODE_MINUS;
    // case KeyCode::Multiply:
    // case KeyCode::Divide:
    case KeyCode::Left:
        return SDL_SCANCODE_LEFT;
    case KeyCode::Right:
        return SDL_SCANCODE_RIGHT;
    case KeyCode::Up:
        return SDL_SCANCODE_UP;
    case KeyCode::Down:
        return SDL_SCANCODE_DOWN;
    case KeyCode::Numpad0:
        return SDL_SCANCODE_KP_0;
    case KeyCode::Numpad1:
        return SDL_SCANCODE_KP_1;
    case KeyCode::Numpad2:
        return SDL_SCANCODE_KP_2;
    case KeyCode::Numpad3:
        return SDL_SCANCODE_KP_3;
    case KeyCode::Numpad4:
        return SDL_SCANCODE_KP_4;
    case KeyCode::Numpad5:
        return SDL_SCANCODE_KP_5;
    case KeyCode::Numpad6:
        return SDL_SCANCODE_KP_6;
    case KeyCode::Numpad7:
        return SDL_SCANCODE_KP_7;
    case KeyCode::Numpad8:
        return SDL_SCANCODE_KP_8;
    case KeyCode::Numpad9:
        return SDL_SCANCODE_KP_9;
    case KeyCode::F1:
        return SDL_SCANCODE_F1;
    case KeyCode::F2:
        return SDL_SCANCODE_F2;
    case KeyCode::F3:
        return SDL_SCANCODE_F3;
    case KeyCode::F4:
        return SDL_SCANCODE_F4;
    case KeyCode::F5:
        return SDL_SCANCODE_F5;
    case KeyCode::F6:
        return SDL_SCANCODE_F6;
    case KeyCode::F7:
        return SDL_SCANCODE_F7;
    case KeyCode::F8:
        return SDL_SCANCODE_F8;
    case KeyCode::F9:
        return SDL_SCANCODE_F9;
    case KeyCode::F10:
        return SDL_SCANCODE_F10;
    case KeyCode::F11:
        return SDL_SCANCODE_F11;
    case KeyCode::F12:
        return SDL_SCANCODE_F12;
    case KeyCode::F13:
        return SDL_SCANCODE_F13;
    case KeyCode::F14:
        return SDL_SCANCODE_F14;
    case KeyCode::F15:
        return SDL_SCANCODE_F15;
    case KeyCode::Pause:
        return SDL_SCANCODE_PAUSE;

    default:
        return SDL_SCANCODE_0;
    }
}

} // namespace

bool libKeyValue(jt::KeyCode k)
{
    auto const* const keyState = SDL_GetKeyboardState(nullptr);
    return keyState[toLib(k)] == 1;
}
} // namespace jt
