//
// Created by SF on 01.07.25.
//

module;
#include <print>

module SharedState;

import :SharedContext;
import :BaseState;
import Logger;
QuitState::QuitState(SharedContext* l_context)
    : BaseState(l_context) {
    Logger::getInstance().log("QuitState::QuitState");
}
QuitState::~QuitState() {
    std::println("QuitState::~QuitState");
    Logger::getInstance().log("QuitState::~QuitState");
}

void QuitState::on_create() {
    std::println("QuitState::onCreate");
}

void QuitState::on_activate() {
    std::println("QuitState::onActivate");
}
void QuitState::on_deactivate()  {
    std::println("QuitState::onDeactivate");
}
void QuitState::on_destroy() {
    std::println("QuitState::onDestroy");
    m_shared_context->m_stateManager->print_states_to_console();
}

void QuitState::update(float l_dt) {
    std::println("QuitState::update");
    m_shared_context->m_stateManager->switch_state(StateType::Menu);
    m_shared_context->m_stateManager->remove_state(StateType::Quit);

}
void QuitState::draw() { }