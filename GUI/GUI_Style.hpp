//
// Created by Keen on 07/02/2022.
//

#ifndef ENEMATA_GUI_STYLE_HPP
#define ENEMATA_GUI_STYLE_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
// GUI_Element_State and GUI_Style are coupled in GUI_Element.hpp as
// using ElementStyles = std::unordered_map<GUI_Element_State, GUI_Style>;

enum class GUI_Element_State{
    Neutral, Focused, Clicked
};

struct GUI_Style {
    GUI_Style();
    ~GUI_Style() = default;

    sf::Vector2f            m_ElementSize;
    sf::Vector2f            m_textPadding;
    sf::Vector2f            m_glyphPadding;

    sf::Color               m_backgroundColor;
    sf::Color               m_backgroundImageColor;
    sf::Color               m_elementColor;
    sf::Color               m_textColor;

    std::string             m_backgroundImageStr;
    std::string m_glyph;
    std::string             m_textFontStr;

    unsigned int            m_textSize;
    bool                    m_textCenterOrigin;
};

struct GUI_Visual{
    sf::RectangleShape  m_backgroundSolid;
    sf::Sprite          m_backgroundImage;
    sf::Sprite          m_glyph; 
    sf::Text            m_text;
};

#endif //ENEMATA_GUI_STYLE_HPP
