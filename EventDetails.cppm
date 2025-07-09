//
// Created by CommanderKeen on 12.10.24.
//
module;
#include <cstdint>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
export module SharedState:EventDetails;


export struct EventDetails{
    EventDetails() = default;
    ~EventDetails() = default;

    sf::Vector2u            m_size{0,0 }; // window size
    sf::Vector2i            m_position{0,0}; // mouse position
    std::uint32_t           m_unicode{UINT32_MAX}; // text entered
    sf::Keyboard::Key       m_key{};
    sf::Mouse::Button       m_button{}; //!< Code of the button that has been pressed

    void clear(){
        m_size = sf::Vector2u{0,0};
        m_position = sf::Vector2i{0,0};
        m_unicode = UINT32_MAX;
        m_key = sf::Keyboard::Key{};
        m_button = sf::Mouse::Button{};
    }
};