//
// Created by SF on 01.07.25.
//

module;
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>

module SharedState;

import :SharedContext;
import :BaseState;
import Logger;
import Utils;

QuitState::QuitState(SharedContext* l_context)
    : BaseState(l_context), m_font(Utils::formatPath(Utils::get_project_path() + "\\" + "resources/fonts/arial_unicode.ttf")){
    Logger::getInstance().log("QuitState::QuitState");
    m_shared_context->m_eventManager->registerCallback(StateType::Quit,
                                                       "arrow_key_left",
                                                       &QuitState::arrow_key_left,
                                                       this);
    m_shared_context->m_eventManager->registerCallback(StateType::Quit,
                                                       "arrow_key_right",
                                                       &QuitState::arrow_key_right,
                                                       this);
    m_shared_context->m_eventManager->registerCallback(StateType::Quit,
                                                       "select",
                                                       &QuitState::select,
                                                       this);

    m_is_transparent = true;
    m_is_transcendent = false;
    m_gui_container = std::make_unique<Gui_Container>();
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
    m_gui_container->render(m_shared_context->m_window->getRenderWindow());
}

void QuitState::setupGui(){
    std::unique_ptr<Label> m_label = std::make_unique<Label>(&m_font);
    m_label->setText("Do you want to quit?");

    std::unique_ptr<Button> button1 = std::make_unique<Button>(&m_font);
    button1->setText("Yes");
    button1->setPosition({0.f, 25.f});
    button1->setCallback([this]() {
        m_shared_context->m_stateManager->clear();
    });
    std::unique_ptr<Button> button2 = std::make_unique<Button>(&m_font);
    button2->setText("No");
    button2->setPosition({60.f, 25.f});
    button2->setCallback([this]() {
        m_shared_context->m_stateManager->switch_state(StateType::Menu);
    });
    m_gui_container->add_child(std::move(m_label));
    m_gui_container->add_child(std::move(button1));
    m_gui_container->add_child(std::move(button2));
    m_gui_container->selectElementAt(1);
}

void QuitState::arrow_key_left(EventDetails* l_details){
    Logger::getInstance().log("QuitState::keyArrowUp");

    m_gui_container->select_previous_selectable();
}

void QuitState::arrow_key_right(EventDetails* l_details){
    Logger::getInstance().log("QuitState::keyArrowDown");
    m_gui_container->select_next_selectable();

}
void QuitState::select(EventDetails* l_details){
    Logger::getInstance().log("QuitState::select");
    m_gui_container->on_click();
}