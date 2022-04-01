//
// Created by Keen on 23/10/2021.
//

#include "StateManager.hpp"
#include "MenuState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"
#include "OptionState.hpp"
#include <iostream>
StateManager::StateManager(SharedContext* l_sharedContext)
: m_sharedContext(l_sharedContext){
    registerState<MenuState>(StateType::Menu);
    registerState<GameState>(StateType::Game);
    registerState<PauseState>(StateType::Pause);
    registerState<OptionState>(StateType::Options);
}

void StateManager::update(const float &l_dt) {
    for(auto& pair : m_states){
        pair.second->update();
    }
    while(m_statesToRemove.begin() != m_statesToRemove.end()){
        remove(m_statesToRemove.front());
    }
}

void StateManager::draw() {
    for(auto& pair : m_states){
        pair.second->draw();
    }
}

void StateManager::switchState(StateType l_stateType) {
    for(auto i = 0; i < m_states.size(); ++i){
        if(m_states[i].first == l_stateType){
            m_states.emplace_back(l_stateType, std::move(m_states[i].second));
            m_states.erase(m_states.begin() + i);
            return;
        }
    }
    if(!create(l_stateType)){
        std::cout << "Warning in StateManager::switchState: could not create State with StateType "
        << int(l_stateType) << "\n";
    }
    m_states.back().second->activate();
}

bool StateManager::create(StateType l_stateType) {
    auto foundTemplate = m_factory.find(l_stateType);
    if(foundTemplate == m_factory.end()){
        return false;
    }
    auto state = foundTemplate->second();
    state->initialize();
    m_states.emplace_back(l_stateType, std::move(state));
    return true;
}

void StateManager::removeState(StateType l_stateType) {
    m_statesToRemove.emplace_back(l_stateType);
}

bool StateManager::hasState(StateType l_stateType) const {
    // if state is found in remove-list treat it as not existing
    if(std::find(m_statesToRemove.begin(), m_statesToRemove.end(), l_stateType) != m_statesToRemove.end()){
        return false;
    }
    auto found = std::find_if(m_states.begin(), m_states.end(), [&l_stateType](const auto& pair){
        return l_stateType == pair.first;
    });
    return found != m_states.end();
}

void StateManager::remove(StateType l_stateType) {
    if(hasState(l_stateType)){
        auto remove = std::remove_if(m_states.begin(), m_states.end(), [&l_stateType](const auto& pair){
            return pair.first == l_stateType;
        });
        m_states.erase(remove);
    }
}
