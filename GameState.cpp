//
// Created by CommanderKeen on 13.02.25.
//


module;
#include <print>
#include <SFML/Graphics/RenderWindow.hpp>

module SharedState;

import Logger;

GameState::GameState(SharedContext* l_context)
    : BaseState(l_context)
{
    std::println("GameState::GameState");
    Logger::getInstance().log("GameState::GameState");
}
GameState::~GameState(){
    std::println("GameState::~GameState");
}

void GameState::on_create(){
    std::println("GameState::onCreate");
    Logger::getInstance().log("GameState::on_create");
}
void GameState::on_activate() {
    std::println("GameState::onActivate");
    Logger::getInstance().log("GameState::on_activate");
    m_shared_context->m_stateManager->print_states_to_console();
}
void GameState::on_deactivate() {
    std::println("GameState::ondeactivate");
    Logger::getInstance().log("GameState::on_deactivate");
}
void GameState::on_destroy() {
    std::println("GameState::ondestroy");
    Logger::getInstance().log("GameState::on_destroy");
}
void GameState::update(float l_dt) {}
void GameState::draw() {

}

void GameState::switch_to_Menu(){

}