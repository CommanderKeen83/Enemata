//
// Created by Keen on 30/10/2021.
//

#include "GUI_Interface.hpp"
#include "../Logger.hpp"
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>
#include "../Utils.hpp"


GUI_Interface::GUI_Interface(const std::string l_name, GUI_Manager *l_gui_manager)
// every interface is logically a Window. Also, it cannot be owned by other GUI_Elements, but it owns all GUI_Elements
// attached to itself
: GUI_Element(l_name, GUI_Element_Type::Window, this){
    Logger::getInstance().log("created GUI_Interface with name: " + l_name);
    m_backdropTexture = std::make_unique<sf::RenderTexture>();
    m_contentTexture = std::make_unique<sf::RenderTexture>();
    m_controlTexture = std::make_unique<sf::RenderTexture>();
}

void GUI_Interface::redraw() {
    /**
     * eventually create backdropTexture
     * clear backdropTexture
     * draw to backdropTexture
     * display backdropTexture
     * **/

    m_backdropSprite.setTexture(m_backdropTexture->getTexture());

    /**
     * m_backdropSprite set TextureRect
     * **/
}

void GUI_Interface::draw(sf::RenderWindow* l_renderWindow) {
    l_renderWindow->draw(m_backdropSprite);
    l_renderWindow->draw(m_contentSprite);
    l_renderWindow->draw(m_controlSprite);
}

std::string GUI_Interface::getName() const {
    return m_name;
}

void GUI_Interface::readLine(std::stringstream &l_ss) {

    std::string movable{};
    std::string showTitle{};
    std::string title{};

    l_ss >> m_elementPadding.x >> m_elementPadding.y >>  movable >> showTitle >> title;
    Utils::toLower(movable);
    Utils::toLower(showTitle);

    m_visual.m_text.setString(title);

    // if  immovable/notitle is explicitly passed, set it to false, otherwise its activated.
    m_isMovable = movable == "immovable" ? false : true;
    m_showTitleBar = showTitle == "notitle" ? false : true;
}

void GUI_Interface::toggleTitleBar() {
    m_showTitleBar = !m_showTitleBar;
}
