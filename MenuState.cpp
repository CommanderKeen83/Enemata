//
// Created by Keen on 23/10/2021.
//

#include "MenuState.hpp"
#include "StateManager.hpp"
#include "Window.hpp"
#include "TextureManager.hpp"
#include "GUI/GUI_Manager.hpp"

MenuState::MenuState(StateManager* l_stateManager)
: BaseState(l_stateManager) {

}

void MenuState::initialize() {
    auto& menu_background_texture = *m_stateManager->getContext()->m_textureManager->getResource("menu_background");
    m_backgroundSprite.setTexture(menu_background_texture);

    m_view.setSize(menu_background_texture.getSize().x, menu_background_texture.getSize().y);
    m_view.setCenter(menu_background_texture.getSize().x / 2.f, menu_background_texture.getSize().y / 2.f);
    m_stateManager->getContext()->m_window->getRenderWindow()->setView(m_view);

    auto* gui_manager = m_stateManager->getContext()->m_gui_manager;
    gui_manager->loadInterface(StateType::Menu, "MainMenu.interface", "MainMenu");
}

void MenuState::activate() {

}

void MenuState::deActivate() {

}

void MenuState::destroy() {

}

void MenuState::update() {

}

void MenuState::draw() {
    m_stateManager->getContext()->m_window->getRenderWindow()->draw(m_backgroundSprite);

}
