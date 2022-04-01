//
// Created by Keen on 24/10/2021.
//

#ifndef ENEMATA_GUI_EVENT_HPP
#define ENEMATA_GUI_EVENT_HPP

#include <string>
#include <SFML/System/Vector2.hpp>
enum class GUI_EventType{
    None, Click, Release, Hover, Leave
};

struct GUI_Event{
    GUI_EventType           m_guiEventType;
    std::string             m_element;
    std::string             m_interface;
    sf::Vector2f            m_coordinates;
};

#endif //ENEMATA_GUI_EVENT_HPP
