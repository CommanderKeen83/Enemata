//
// Created by CommanderKeen on 15.12.24.
//
module;
#include <functional>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

module SharedState;

import Logger;
import Utils;
import :EventManager;

MenuState::MenuState(SharedContext* l_context)
: BaseState(l_context), m_backgroundTexture(), m_backgroundSprite(), m_font("Arial.ttf"),
m_gui_buttons(), m_selected_item(0){
    Logger::getInstance().log("MenuState::MenuState");
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

    setupGUI();
    m_font.setSmooth(false);
}
MenuState::~MenuState() {
    Logger::getInstance().log("MenuState::~MenuState");
    m_shared_context->m_eventManager->removeCallback(StateType::Menu, "arrowKeyUp");
    m_shared_context->m_eventManager->removeCallback(StateType::Menu, "arrowKeyDown");
}

void MenuState::on_create() {
    Logger::getInstance().log("MenuState::on_create()");
    std::string filePath = Utils::get_project_path() + "/resources/graphics/main_menu.png";
    m_backgroundTexture = std::make_unique<sf::Texture>();
    if(!m_backgroundTexture->loadFromFile(filePath)){
        Logger::getInstance().log("MenuState::oncreate - could not load backgroundtexture");
    }
    m_backgroundSprite = std::make_unique<sf::Sprite>(*m_backgroundTexture);
    m_view = sf::View{sf::Vector2f{float(m_backgroundTexture->getSize().x / 2), float(m_backgroundTexture->getSize().y / 2)},
                      sf::Vector2f{float(m_backgroundTexture->getSize().x), float(m_backgroundTexture->getSize().y)}};
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

void MenuState::update(float l_dt){

}

void MenuState::draw(){
    m_shared_context->m_window->getRenderWindow()->draw(*m_backgroundSprite);
    for (auto& button : m_gui_buttons) {
         button->draw(m_shared_context->m_window->getRenderWindow());
    }
}

void MenuState::setupGUI() {
    auto new_game_button = std::make_unique<Button>(&m_font);
    new_game_button->setText("New Game");
    new_game_button->setTextSize(10);
    new_game_button->setPosition({100.f,100.f});
    new_game_button->setTextFillColor(sf::Color::White);
    new_game_button->setCallback(std::bind(&MenuState::startGame, this));

    auto options_game_button = std::make_unique<Button>(&m_font);
    options_game_button->setText("Options");
    options_game_button->setTextSize(10);
    options_game_button->setPosition({100.f,110.f});
    options_game_button->setTextFillColor(sf::Color::White);

    auto quit_game_button = std::make_unique<Button>(&m_font);
    quit_game_button->setText("Quit");
    quit_game_button->setTextSize(10);
    quit_game_button->setPosition({100.f,120.f});
    quit_game_button->setTextFillColor(sf::Color::White);
    quit_game_button->setCallback(std::bind(&MenuState::quitGame, this));
    m_gui_buttons.push_back(std::move(new_game_button));
    m_gui_buttons.push_back(std::move(options_game_button));
    m_gui_buttons.push_back(std::move(quit_game_button));

    m_gui_buttons[m_selected_item]->setTextFillColor(sf::Color::Red);
}
void MenuState::quitGame() {
    m_shared_context->m_stateManager->switch_state(StateType::Exit);
}
void MenuState::startGame() {
    m_shared_context->m_stateManager->switch_state(StateType::Game);
}


void MenuState::keyArrowUp(EventDetails* l_details){
    Logger::getInstance().log("MenuState::keyArrowUp");
    m_gui_buttons[m_selected_item]->setTextFillColor(sf::Color::White);
    m_selected_item = (m_selected_item - 1);
    if (m_selected_item < 0) m_selected_item = m_gui_buttons.size() - 1;

    m_gui_buttons[m_selected_item]->setTextFillColor(sf::Color::Red);
}

void MenuState::keyArrowDown(EventDetails* l_details){
    Logger::getInstance().log("MenuState::keyArrowDown");


    m_gui_buttons[m_selected_item]->setTextFillColor(sf::Color::White);
    m_selected_item = (m_selected_item + 1) % m_gui_buttons.size();
    m_gui_buttons[m_selected_item]->setTextFillColor(sf::Color::Red);

}

void MenuState::select(EventDetails* l_details){
    Logger::getInstance().log("MenuState::select");
    m_gui_buttons[m_selected_item]->on_click();

}