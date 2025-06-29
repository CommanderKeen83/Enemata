//
// Created by CommanderKeen on 12.10.24.
//
module;
#include <variant>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
export module SharedState:EventInfo;


export struct EventInfo{
    EventInfo(std::variant<sf::Keyboard::Key, sf::Mouse::Button> l_code)
    : m_code(l_code){}
    EventInfo() : EventInfo(sf::Keyboard::Key::Unknown) {}

    std::variant<sf::Keyboard::Key, sf::Mouse::Button> m_code;
};