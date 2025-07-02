//
// Created by SF on 01.07.25.
//

module;
#include <print>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>

module SharedState;

import :SharedContext;
import :BaseState;
import Logger;
QuitState::QuitState(SharedContext* l_context)
    : BaseState(l_context), m_font("Arial.ttf"){
    Logger::getInstance().log("QuitState::QuitState");
    m_shared_context->m_eventManager->registerCallback(StateType::Quit,
                                                       "arrowKeyUp",
                                                       &QuitState::keyArrowUp,
                                                       this);
    m_shared_context->m_eventManager->registerCallback(StateType::Quit,
                                                       "arrowKeyDown",
                                                       &QuitState::keyArrowDown,
                                                       this);
    m_shared_context->m_eventManager->registerCallback(StateType::Quit,
                                                       "select",
                                                       &QuitState::select,
                                                       this);


    setupGui();
}
QuitState::~QuitState() {
    Logger::getInstance().log("QuitState::~QuitState");
}

void QuitState::on_create() {
    Logger::getInstance().log("QuitState::on_create");
}

void QuitState::on_activate() {
    Logger::getInstance().log("QuitState::on_activate");

}
void QuitState::on_deactivate()  {
    Logger::getInstance().log("QuitState::deactivate");
}
void QuitState::on_destroy() {
    Logger::getInstance().log("QuitState::on_destroy");
}

void QuitState::update(float l_dt) {

}
void QuitState::draw() {
    m_label->draw(m_shared_context->m_window->getRenderWindow());
    for(auto& gui_element : m_buttons){
        gui_element->draw(m_shared_context->m_window->getRenderWindow());
    }
}

void QuitState::setupGui(){
    m_label = std::make_unique<Label>(&m_font);
    m_label->setText("Do you want to quit?");

    std::unique_ptr<Button> button1 = std::make_unique<Button>(&m_font);
    button1->setText("Yes");
    button1->setPosition({0.f, 25.f});
    button1->set_text_fill_color(sf::Color::Red);
    button1->setCallback([this]() {
        m_shared_context->m_stateManager->clear();
    });
    std::unique_ptr<Button> button2 = std::make_unique<Button>(&m_font);
    button2->setText("No");
    button2->setPosition({60.f, 25.f});
    m_buttons.emplace_back(std::move(button1));
    m_buttons.emplace_back(std::move(button2));

}

void QuitState::keyArrowUp(EventDetails* l_details){
    Logger::getInstance().log("QuitState::keyArrowUp");

    m_buttons[m_selected_button]->set_text_fill_color(sf::Color::White);
    m_selected_button = (m_selected_button - 1);
    if (m_selected_button < 0) m_selected_button = m_buttons.size() - 1;

    m_buttons[m_selected_button]->set_text_fill_color(sf::Color::Red);
}

void QuitState::keyArrowDown(EventDetails* l_details){
    Logger::getInstance().log("QuitState::keyArrowDown");

    m_buttons[m_selected_button]->set_text_fill_color(sf::Color::White);
    m_selected_button = (m_selected_button + 1) % m_buttons.size();
    m_buttons[m_selected_button]->set_text_fill_color(sf::Color::Red);

}
void QuitState::select(EventDetails* l_details){
    m_buttons[m_selected_button]->on_click();
}