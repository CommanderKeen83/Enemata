//
// Created by Keen on 23/10/2021.
//

#ifndef ENEMATA_MENUSTATE_HPP
#define ENEMATA_MENUSTATE_HPP

#include "BaseState.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
class MenuState : public BaseState{
public:
    MenuState(StateManager* l_stateManager);
    ~MenuState() override = default;

    void initialize() override;

    void activate() override;

    void deActivate() override;

    void destroy() override;

    void update() override;

    void draw() override;

private:
    sf::Sprite      m_backgroundSprite;
    sf::Texture     m_texture;
};


#endif //ENEMATA_MENUSTATE_HPP
