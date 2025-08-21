//
// Created by CommanderKeen on 10.10.24.
//
module;
#include <stdexcept>
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

import Utils;
export module SharedState:EventType;
export enum class EventType{
        Closed,
        Resized,
        LostFocus,
        GainedFocus,
        TextEntered,
        KeyPressed,
        KeyReleased,
        MouseWheelScrolled,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseMovedRaw,
        MouseEntered,
        MouseLeft,
        JoystickButtonPressed,
        JoystickButtonReleased,
        JoystickMoved,
        JoystickConnected,
        JoystickDisconnected,
        RealTimeKeyboard,
        RealTimeMouse
};
export EventType get_EventType_from_string(const std::string& l_event){
    if (l_event == "Closed") { return EventType::Closed; }
    else if(l_event == "Resized") { return EventType::Resized; }
    else if(l_event == "LostFocus") { return EventType::LostFocus; }
    else if(l_event == "GainedFocus") { return EventType::GainedFocus; }
    else if(l_event == "TextEntered") { return EventType::TextEntered; }
    else if(l_event == "KeyPressed") { return EventType::KeyPressed; }
    else if(l_event == "KeyReleased") { return EventType::KeyReleased; }
    else if(l_event == "MouseWheelScrolled") { return EventType::MouseWheelScrolled; }
    else if(l_event == "MouseButtonPressed") { return EventType::MouseButtonPressed; }
    else if(l_event == "MouseButtonReleased") { return EventType::MouseButtonReleased; }
    else if(l_event == "MouseMoved") { return EventType::MouseMoved; }
    else if(l_event == "MouseMovedRaw") { return EventType::MouseMovedRaw; }
    else if(l_event == "MouseEntered") { return EventType::MouseEntered; }
    else if(l_event == "MouseLeft") { return EventType::MouseLeft; }
    else if(l_event == "JoystickButtonPressed") { return EventType::JoystickButtonPressed; }
    else if(l_event == "JoystickButtonReleased") { return EventType::JoystickButtonReleased; }
    else if(l_event == "JoystickMoved") { return EventType::JoystickMoved; }
    else if(l_event == "JoystickConnected") { return EventType::JoystickConnected; }
    else if(l_event == "JoystickDisconnected") { return EventType::JoystickDisconnected; }
    else if(l_event == "RealTimeKeyboard") { return EventType::RealTimeKeyboard; }
    else if(l_event == "RealTimeMouse") { return EventType::RealTimeMouse; }
    else {
        throw std::runtime_error("Error in EventType.ccpm::get_EventTime_from_string(...): "
                                 "Could not cmake-debug-build EventType from provided string " +
                                 l_event);
    }
}

export template <typename SFML_Event>
SFML_Event convert_EventType_to_SFMLEventType(EventType l_eventType){
    switch(l_eventType){
        case (EventType::Closed):                   return sf::Event::Closed{};
        case (EventType::Resized):                  return sf::Event::Resized{};
        case (EventType::LostFocus):                return sf::Event::FocusLost{};
        case (EventType::GainedFocus):              return sf::Event::FocusGained{};
        case (EventType::TextEntered):              return sf::Event::TextEntered{};
        case (EventType::KeyPressed):               return sf::Event::KeyPressed{};
        case (EventType::KeyReleased):              return sf::Event::KeyReleased{};
        case (EventType::MouseWheelScrolled):       return sf::Event::MouseWheelScrolled{};
        case (EventType::MouseButtonPressed):       return sf::Event::MouseButtonPressed{};
        case (EventType::MouseButtonReleased):      return sf::Event::MouseButtonReleased{};
        case (EventType::MouseMoved):               return sf::Event::MouseMoved{};
        case (EventType::MouseMovedRaw):            return sf::Event::MouseMovedRaw{};
        case (EventType::MouseEntered):             return sf::Event::MouseEntered{};
        case (EventType::MouseLeft):                return sf::Event::MouseLeft{};
        case (EventType::JoystickButtonPressed):    return sf::Event::JoystickButtonPressed{};
        case (EventType::JoystickButtonReleased):   return sf::Event::JoystickButtonReleased{};
        case (EventType::JoystickMoved):            return sf::Event::JoystickMoved{};
        case (EventType::JoystickConnected):        return sf::Event::JoystickConnected{};
        case (EventType::JoystickDisconnected):     return sf::Event::JoystickDisconnected{};
        default: {
            throw std::runtime_error("Error in EventType.ccpm::convert_SFMLEventType_to_EventType(...): "
                                     "could not convert provided EventType with the value " + std::to_string(static_cast<int>(l_eventType)));
        }
    }
}

EventType convert_SFMLEventtype_to_EventType(const sf::Event& l_sfml_event){
    if(l_sfml_event.is<sf::Event::Closed>())                         return EventType::Closed;
    else if(l_sfml_event.is<sf::Event::Resized>())                   return EventType::Resized;
    else if(l_sfml_event.is<sf::Event::FocusLost>())                 return EventType::LostFocus;
    else if(l_sfml_event.is<sf::Event::FocusGained>())               return EventType::GainedFocus;
    else if(l_sfml_event.is<sf::Event::TextEntered>())               return EventType::TextEntered;
    else if(l_sfml_event.is<sf::Event::KeyPressed>())                return EventType::KeyPressed;
    else if(l_sfml_event.is<sf::Event::KeyReleased>())               return EventType::KeyReleased;
    else if(l_sfml_event.is<sf::Event::MouseWheelScrolled>())        return EventType::MouseWheelScrolled;
    else if(l_sfml_event.is<sf::Event::MouseButtonPressed>())        return EventType::MouseButtonPressed;
    else if(l_sfml_event.is<sf::Event::MouseButtonReleased>())       return EventType::MouseButtonReleased;
    else if(l_sfml_event.is<sf::Event::MouseMoved>())                return EventType::MouseMoved;
    else if(l_sfml_event.is<sf::Event::MouseMovedRaw>())             return EventType::MouseMovedRaw;
    else if(l_sfml_event.is<sf::Event::MouseEntered>())              return EventType::MouseEntered;
    else if(l_sfml_event.is<sf::Event::MouseLeft>())                 return EventType::MouseLeft;
    else if(l_sfml_event.is<sf::Event::JoystickButtonPressed>())     return EventType::JoystickButtonPressed;
    else if(l_sfml_event.is<sf::Event::JoystickButtonReleased>())    return EventType::JoystickButtonReleased;
    else if(l_sfml_event.is<sf::Event::JoystickMoved>())             return EventType::JoystickMoved;
    else if(l_sfml_event.is<sf::Event::JoystickConnected>())         return EventType::JoystickConnected;
    else if(l_sfml_event.is<sf::Event::JoystickDisconnected>())      return EventType::JoystickDisconnected;
    else throw std::runtime_error("Error in EventType::convert_SFMLEventType_to_EventType(...): No appropriate SFML-Event received.");
}
std::variant<sf::Keyboard::Key,sf::Mouse::Button> get_input_from_string(const std::string& l_key){
    std::string lowercase_key = Utils::to_lower(l_key);
         if(lowercase_key == "a") return sf::Keyboard::Key::A;            //!< The A key
    else if(lowercase_key == "b") return sf::Keyboard::Key::B;            //!< The B key
    else if(lowercase_key == "c") return sf::Keyboard::Key::C;            //!< The C key
    else if(lowercase_key == "d") return sf::Keyboard::Key::D;            //!< The D key
    else if(lowercase_key == "e") return sf::Keyboard::Key::E;            //!< The E key
    else if(lowercase_key == "f") return sf::Keyboard::Key::F;            //!< The F key
    else if(lowercase_key == "g") return sf::Keyboard::Key::G;            //!< The G key
    else if(lowercase_key == "h") return sf::Keyboard::Key::H;            //!< The H key
    else if(lowercase_key == "i") return sf::Keyboard::Key::I;            //!< The I key
    else if(lowercase_key == "j") return sf::Keyboard::Key::J;            //!< The J key
    else if(lowercase_key == "k") return sf::Keyboard::Key::K;            //!< The K key
    else if(lowercase_key == "l") return sf::Keyboard::Key::L;            //!< The L key
    else if(lowercase_key == "m") return sf::Keyboard::Key::M;            //!< The M key
    else if(lowercase_key == "n") return sf::Keyboard::Key::N;            //!< The N key
    else if(lowercase_key == "o") return sf::Keyboard::Key::O;            //!< The O key
    else if(lowercase_key == "p") return sf::Keyboard::Key::P;            //!< The P key
    else if(lowercase_key == "q") return sf::Keyboard::Key::Q;            //!< The Q key
    else if(lowercase_key == "r") return sf::Keyboard::Key::R;            //!< The R key
    else if(lowercase_key == "s") return sf::Keyboard::Key::S;            //!< The S key
    else if(lowercase_key == "t") return sf::Keyboard::Key::T;            //!< The T key
    else if(lowercase_key == "u") return sf::Keyboard::Key::U;            //!< The U key
    else if(lowercase_key == "v") return sf::Keyboard::Key::V;            //!< The V key
    else if(lowercase_key == "w") return sf::Keyboard::Key::W;            //!< The W key
    else if(lowercase_key == "x") return sf::Keyboard::Key::X;            //!< The X key
    else if(lowercase_key == "y") return sf::Keyboard::Key::Y;            //!< The Y key
    else if(lowercase_key == "z") return sf::Keyboard::Key::Z;            //!< The Z key
    else if(lowercase_key == "num0") return sf::Keyboard::Key::Num0;         //!< The 0 key
    else if(lowercase_key == "num1") return sf::Keyboard::Key::Num1;         //!< The 1 key
    else if(lowercase_key == "num2") return sf::Keyboard::Key::Num2;         //!< The 2 key
    else if(lowercase_key == "num3") return sf::Keyboard::Key::Num3;         //!< The 3 key
    else if(lowercase_key == "num4") return sf::Keyboard::Key::Num4;         //!< The 4 key
    else if(lowercase_key == "num5") return sf::Keyboard::Key::Num5;         //!< The 5 key
    else if(lowercase_key == "num6") return sf::Keyboard::Key::Num6;         //!< The 6 key
    else if(lowercase_key == "num7") return sf::Keyboard::Key::Num7;         //!< The 7 key
    else if(lowercase_key == "num8") return sf::Keyboard::Key::Num8;         //!< The 8 key
    else if(lowercase_key == "num9") return sf::Keyboard::Key::Num9;         //!< The 9 key
    else if(lowercase_key == "escape") return sf::Keyboard::Key::Escape;       //!< The Escape key
    else if(lowercase_key == "lcontrol") return sf::Keyboard::Key::LControl;   //!< The left Control key
    else if(lowercase_key == "lshift") return sf::Keyboard::Key::LShift;       //!< The left Shift key
    else if(lowercase_key == "lalt") return sf::Keyboard::Key::LAlt;           //!< The left Alt key
    else if(lowercase_key == "lsystem") return sf::Keyboard::Key::LSystem;     //!< The left OS specific key: window (Windows and Linux), apple (macOS), ...
    else if(lowercase_key == "rcontrol") return sf::Keyboard::Key::RControl;   //!< The right Control key
    else if(lowercase_key == "rshift") return sf::Keyboard::Key::RShift;       //!< The right Shift key
    else if(lowercase_key == "ralt") return sf::Keyboard::Key::RAlt;           //!< The right Alt key
    else if(lowercase_key == "rystem") return sf::Keyboard::Key::RSystem;      //!< The right OS specific key: window (Windows and Linux), apple (macOS), ...
    else if(lowercase_key == "menu") return sf::Keyboard::Key::Menu;           //!< The Menu key
    else if(lowercase_key == "lbracket") return sf::Keyboard::Key::LBracket;   //!< The [ key
    else if(lowercase_key == "rbracket") return sf::Keyboard::Key::RBracket;   //!< The ] key
    else if(lowercase_key == "semicolon") return sf::Keyboard::Key::Semicolon; //!< The ; key
    else if(lowercase_key == "comma") return sf::Keyboard::Key::Comma;         //!< The , key
    else if(lowercase_key == "period") return sf::Keyboard::Key::Period;       //!< The . key
    else if(lowercase_key == "apostrophe") return sf::Keyboard::Key::Apostrophe;  //!< The ' key
    else if(lowercase_key == "slash") return sf::Keyboard::Key::Slash;            //!< The / key
    else if(lowercase_key == "backslash") return sf::Keyboard::Key::Backslash;    //!< The \ key
    else if(lowercase_key == "grave") return sf::Keyboard::Key::Grave;            //!< The ` key
    else if(lowercase_key == "equal") return sf::Keyboard::Key::Equal;            //!< The = key
    else if(lowercase_key == "hyphen") return sf::Keyboard::Key::Hyphen;          //!< The - key (hyphen)
    else if(lowercase_key == "space") return sf::Keyboard::Key::Space;            //!< The Space key
    else if(lowercase_key == "enter") return sf::Keyboard::Key::Enter;            //!< The Enter/Return keys
    else if(lowercase_key == "backspace") return sf::Keyboard::Key::Backspace;    //!< The Backspace key
    else if(lowercase_key == "tab") return sf::Keyboard::Key::Tab;                //!< The Tabulation key
    else if(lowercase_key == "pageup") return sf::Keyboard::Key::PageUp;          //!< The Page up key
    else if(lowercase_key == "pagedown") return sf::Keyboard::Key::PageDown;      //!< The Page down key
    else if(lowercase_key == "end") return sf::Keyboard::Key::End;                //!< The End key
    else if(lowercase_key == "home") return sf::Keyboard::Key::Home;              //!< The Home key
    else if(lowercase_key == "insert") return sf::Keyboard::Key::Insert;          //!< The Insert key
    else if(lowercase_key == "delete") return sf::Keyboard::Key::Delete;          //!< The Delete key
    else if(lowercase_key == "add") return sf::Keyboard::Key::Add;                //!< The + key
    else if(lowercase_key == "substract") return sf::Keyboard::Key::Subtract;     //!< The - key (minus, usually from numpad)
    else if(lowercase_key == "multiply") return sf::Keyboard::Key::Multiply;      //!< The * key
    else if(lowercase_key == "divide") return sf::Keyboard::Key::Divide;          //!< The / key
    else if(lowercase_key == "leftarrowkey") return sf::Keyboard::Key::Left;      //!< Left arrow
    else if(lowercase_key == "rightarrowkey") return sf::Keyboard::Key::Right;    //!< Right arrow
    else if(lowercase_key == "uparrowkey") return sf::Keyboard::Key::Up;          //!< Up arrow
    else if(lowercase_key == "downarrowkey") return sf::Keyboard::Key::Down;      //!< Down arrow
    else if(lowercase_key == "numpad0") return sf::Keyboard::Key::Numpad0;        //!< The numpad 0 key
    else if(lowercase_key == "numpad1") return sf::Keyboard::Key::Numpad1;        //!< The numpad 1 key
    else if(lowercase_key == "numpad2") return sf::Keyboard::Key::Numpad2;        //!< The numpad 2 key
    else if(lowercase_key == "numpad3") return sf::Keyboard::Key::Numpad3;        //!< The numpad 3 key
    else if(lowercase_key == "numpad4") return sf::Keyboard::Key::Numpad4;        //!< The numpad 4 key
    else if(lowercase_key == "numpad5") return sf::Keyboard::Key::Numpad5;        //!< The numpad 5 key
    else if(lowercase_key == "numpad6") return sf::Keyboard::Key::Numpad6;        //!< The numpad 6 key
    else if(lowercase_key == "numpad7") return sf::Keyboard::Key::Numpad7;        //!< The numpad 7 key
    else if(lowercase_key == "numpad8") return sf::Keyboard::Key::Numpad8;        //!< The numpad 8 key
    else if(lowercase_key == "numpad9") return sf::Keyboard::Key::Numpad9;        //!< The numpad 9 key
    else if(lowercase_key == "f1") return sf::Keyboard::Key::F1;           //!< The F1 key
    else if(lowercase_key == "f2") return sf::Keyboard::Key::F2;           //!< The F2 key
    else if(lowercase_key == "f3") return sf::Keyboard::Key::F3;           //!< The F3 key
    else if(lowercase_key == "f4") return sf::Keyboard::Key::F4;           //!< The F4 key
    else if(lowercase_key == "f5") return sf::Keyboard::Key::F5;           //!< The F5 key
    else if(lowercase_key == "f6") return sf::Keyboard::Key::F6;           //!< The F6 key
    else if(lowercase_key == "f7") return sf::Keyboard::Key::F7;           //!< The F7 key
    else if(lowercase_key == "f8") return sf::Keyboard::Key::F8;           //!< The F8 key
    else if(lowercase_key == "f9") return sf::Keyboard::Key::F9;           //!< The F9 key
    else if(lowercase_key == "f10") return sf::Keyboard::Key::F10;         //!< The F10 key
    else if(lowercase_key == "f11") return sf::Keyboard::Key::F11;         //!< The F11 key
    else if(lowercase_key == "f12") return sf::Keyboard::Key::F12;         //!< The F12 key
    else if(lowercase_key == "f13") return sf::Keyboard::Key::F13;         //!< The F13 key
    else if(lowercase_key == "f14") return sf::Keyboard::Key::F14;         //!< The F14 key
    else if(lowercase_key == "f15") return sf::Keyboard::Key::F15;         //!< The F15 key
    else if(lowercase_key == "pause") return sf::Keyboard::Key::Pause;     //!< The Pause key
    else if(lowercase_key == "leftmousebutton") return sf::Mouse::Button::Left;
    else if(lowercase_key == "rightmousebutton") return sf::Mouse::Button::Right;
    else if(lowercase_key == "middlemousebutton") return sf::Mouse::Button::Middle;
    else if(lowercase_key == "extra1mousebutton") return sf::Mouse::Button::Extra1;
    else if(lowercase_key == "extra2mousebutton") return sf::Mouse::Button::Extra2;
    else return sf::Keyboard::Key::Unknown;

}
