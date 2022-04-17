//
// Created by Keen on 30/10/2021.
//

#ifndef ENEMATA_GUI_INTERFACE_HPP
#define ENEMATA_GUI_INTERFACE_HPP

#include "GUI_Element.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>


class GUI_Manager;

class GUI_Interface : public GUI_Element{
public:
    GUI_Interface(const std::string& l_name, GUI_Manager* l_gui_manager);

    void redraw();
    void draw(sf::RenderWindow* l_renderWindow);
    std::string getName() const;
    void toggleTitleBar();
private:
    void readLine(std::stringstream& l_ss) override;
    void onClick(const sf::Vector2f &l_mousePosition) override;
    void onHover(const sf::Vector2f &l_mousePosition) override;
    void onLeave() override;
    void onRelease() override;

private:
    std::unique_ptr<sf::RenderTexture> m_backdropTexture;
    std::unique_ptr<sf::RenderTexture> m_contentTexture;
    std::unique_ptr<sf::RenderTexture> m_controlTexture;

    sf::Vector2f    m_elementPadding;

    sf::Sprite m_backdropSprite;
    sf::Sprite m_contentSprite;
    sf::Sprite m_controlSprite;

    bool    m_isMovable;
    bool    m_showTitleBar;

};


#endif //ENEMATA_GUI_INTERFACE_HPP
