//
// Created by CommanderKeen on 13.02.25.
//


module;
#include <SFML/Graphics/RenderWindow.hpp>

module SharedState;

import Logger;
import :Map;
GameState::GameState(SharedContext* l_context)
    : BaseState(l_context)
{
    m_map = std::make_unique<Map>(l_context->m_textureManager, "tileset_level_1");
    m_map->load_map("map1.map");
    Logger::getInstance().log("GameState::GameState");
}
GameState::~GameState(){
    Logger::getInstance().log("GameState::~GameState");
}

void GameState::on_create(){
    Logger::getInstance().log("GameState::on_create");
}
void GameState::on_activate() {
    Logger::getInstance().log("GameState::on_activate");
}
void GameState::on_deactivate() {
    Logger::getInstance().log("GameState::on_deactivate");
}
void GameState::on_destroy() {
    Logger::getInstance().log("GameState::on_destroy");
}
void GameState::update(float l_dt) {}
void GameState::draw() {

}

void GameState::switch_to_Menu(){

}