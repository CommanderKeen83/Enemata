//
// Created by Keen on 30/10/2021.
//

#ifndef ENEMATA_GUI_ELEMENT_HPP
#define ENEMATA_GUI_ELEMENT_HPP

#include "GUI_Style.hpp"
#include <SFML/System/Vector2.hpp>
#include <string>
#include <unordered_map>

class GUI_Interface;
// Window is the visual representation of an Interface
enum class GUI_Element_Type{None = -1, Window, Label, Button, Scrollbar, Testfield};
using ElementStyles = std::unordered_map<GUI_Element_State, GUI_Style>;

class GUI_Element {
public:
    GUI_Element(const std::string& l_name, GUI_Element_Type l_guiElementType, GUI_Interface* l_owner = nullptr);
    virtual ~GUI_Element() = default;
    friend std::stringstream& operator >> (std::stringstream& l_ss, GUI_Element* l_element){
        l_element->readLine(l_ss);
        return l_ss;
    }
protected:
    GUI_Visual          m_visual;
    ElementStyles       m_styles;
    std::string         m_name;
    sf::Vector2f        m_position;
    GUI_Element_Type    m_guiElementType;
    GUI_Element_State   m_currentElementState;
private:
    virtual void readLine(std::stringstream& l_ss) = 0;
};


#endif //ENEMATA_GUI_ELEMENT_HPP
