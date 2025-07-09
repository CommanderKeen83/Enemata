//
// Created by CommanderKeen on 15.12.24.
//
module;

#include <print>
#include <functional>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

module SharedState;

import Logger;
import Utils;


MenuState::MenuState(SharedContext* l_context)
: BaseState(l_context), m_font("Arial.ttf"), m_selected_item(0){
    Logger::getInstance().log("MenuState::MenuState");
    //loading texture "main_menu_background"
    m_shared_context->m_textureManager->loadResource("main_menu_background");
    m_shared_context->m_eventManager->registerCallback(StateType::Menu,
                                                       "arrowKeyUp",
                                                       &MenuState::keyArrowUp,
                                                       this);
    m_shared_context->m_eventManager->registerCallback(StateType::Menu,
                                                       "arrowKeyDown",
                                                       &MenuState::keyArrowDown,
                                                       this);
    m_shared_context->m_eventManager->registerCallback(StateType::Menu,
                                                       "select",
                                                       &MenuState::select,
                                                       this);

    m_button_container = std::make_unique<Gui_Container>();
    setupGUI();
    m_font.setSmooth(false);
}
MenuState::~MenuState() {
    Logger::getInstance().log("MenuState::~MenuState");
    m_shared_context->m_eventManager->removeCallback(StateType::Menu, "arrowKeyUp");
    m_shared_context->m_eventManager->removeCallback(StateType::Menu, "arrowKeyDown");
    m_shared_context->m_eventManager->removeCallback(StateType::Menu ,"select");
}

void MenuState::on_create() {
    Logger::getInstance().log("MenuState::on_create()");
    sf::Texture& background_texture = *m_shared_context->m_textureManager->get("main_menu_background");
    m_backgroundSprite = std::make_unique<sf::Sprite>(background_texture);
    sf::Vector2f center = {float(background_texture.getSize().x) / 2.f, float(background_texture.getSize().y) / 2.f};
    sf::Vector2f size = {float(background_texture.getSize().x), float(background_texture.getSize().y)};
    m_view = sf::View{center,size};
}
void MenuState::on_activate() {
    Logger::getInstance().log("MenuState::on_activate()");
}
void MenuState::on_deactivate(){
    Logger::getInstance().log("MenuState::on_deactivate()");
}
//TODO: on_destroy isn't invoked anywhere yet
void MenuState::on_destroy() {
    Logger::getInstance().log("MenuState::on_destroy()");
}

void MenuState::update(float l_dt) {
    m_button_container->update(l_dt);
}

void MenuState::draw(){
    m_shared_context->m_window->getRenderWindow()->draw(*m_backgroundSprite);
    m_button_container->render(m_shared_context->m_window->getRenderWindow());
}

void MenuState::setupGUI() {
    std::unique_ptr<Button> new_game_button = std::make_unique<Button>(&m_font);
    new_game_button->setText("New Game");
    new_game_button->setTextSize(10);
    new_game_button->setCallback([this]() {
        startGame();
    });

    std::unique_ptr<Button> options_button = std::make_unique<Button>(&m_font);
    options_button->setText("Options");
    options_button->setTextSize(10);
    options_button->setPosition({0.f, 5.f});

    std::unique_ptr<Button> quit_button = std::make_unique<Button>(&m_font);
    quit_button->setText("Quit");
    quit_button->setTextSize(10);
    quit_button->setPosition({0.f, 10.f});
    quit_button->setCallback([this]() {
    quitGame();
});


    m_button_container->add_child(std::move(new_game_button));
    m_button_container->add_child(std::move(options_button));
    m_button_container->add_child(std::move(quit_button));
    // select first option ("new game")
    m_button_container->selectElementAt(2);

    m_button_container->setPosition({100.f,100.f});
}
void MenuState::quitGame() {
    m_shared_context->m_stateManager->switch_state(StateType::Quit);
}
void MenuState::startGame() {
    m_shared_context->m_stateManager->switch_state(StateType::Game);
}


void MenuState::keyArrowUp(EventDetails* l_details){
    Logger::getInstance().log("MenuState::keyArrowUp");
    m_button_container->select_previous_selectable();
}

void MenuState::keyArrowDown(EventDetails* l_details){
    Logger::getInstance().log("MenuState::keyArrowDown");
    m_button_container->select_next_selectable();

}

void MenuState::select(EventDetails* l_details){
    Logger::getInstance().log("MenuState::select");
    m_button_container->on_click<Button>();
//    m_gui_buttons[m_selected_item]->on_click();
}