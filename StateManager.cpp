//
// Created by CommanderKeen on 10.11.24.
//

module;
#include <memory>
#include <vector>
#include <functional>
#include <unordered_map>

module SharedState;

import :Types;
import :MenuState;
import :GameState;
import :SharedContext;
StateManager::StateManager(SharedContext* l_context)
: m_shared_context(l_context){
    register_state<MenuState>(StateType::Menu);
    register_state<GameState>(StateType::Game);
}

void StateManager::update(const float l_dt) {
    // BaseState::m_transcendent is vital here
    if (m_states.empty()) return;
    if(m_states.size() > 1 && m_states.back().second->is_transcendent()){
        auto traverser = m_states.end(); // points no past the last element
        while(traverser != m_states.begin()) {
            traverser--;
            if (!traverser->second->is_transcendent()) {
                break;
            }
        }
        //from here we update all layers from bottom up to top
        for( ; traverser != m_states.end(); traverser++){
            traverser->second->update(l_dt);
        }

    }else{
        m_states.back().second->update(l_dt);
    }
}
void StateManager::draw() {
    if (m_states.empty()) return;
    if(m_states.size() > 1 && m_states.back().second->is_transparent()){
        auto traverser = m_states.end(); // points no past the last element
        while(traverser != m_states.begin()) {
            traverser--;
            if (!traverser->second->is_transparent()) {
                break;
            }
        }
        //from here we update all layers from bottom up to top
        for( ; traverser != m_states.end(); traverser++){
            auto view = traverser->second->getView();
            m_shared_context->m_window->getRenderWindow()->setView(view);
            traverser->second->draw();
        }

    }else{
        auto view = m_states.back().second->getView();
        m_shared_context->m_window->getRenderWindow()->setView(view);
        m_states.back().second->draw();
    }
}

void StateManager::switch_state(StateType l_new_state){
    m_shared_context->m_eventManager->setCurrentState(l_new_state);
    // check if state is already in State-Stack, if so, push it on top to be active State...
    for (auto it = m_states.begin(); it != m_states.end();) {
        if (it->first == l_new_state) {
            auto temp = std::move(it->second);
            m_states.back().second->on_deactivate();
            m_states.emplace_back(l_new_state, std::move(temp));
            m_states.back().second->on_activate();
            m_shared_context->m_window->getRenderWindow()->setView(m_states.back().second->getView());
            m_states.erase(it);
            return;
        } else {
            ++it;
        }
    }
    // before pushing new stack on top, we  must deactivate current state on top of stack, if there is one
    if(!m_states.empty()){
        m_states.back().second->on_deactivate();
    }
    create_state(l_new_state);
    m_states.back().second->on_activate();
    m_shared_context->m_window->getRenderWindow()->setView(m_states.back().second->getView());
    
}
void StateManager::create_state(StateType l_new_state){
    auto foundStateFactory = m_state_factory.find(l_new_state);
    if(foundStateFactory != m_state_factory.end()){
        auto state = foundStateFactory->second(); // creates requested State
        state->on_create();
        m_states.emplace_back(l_new_state, std::move(state));
    }
}
void StateManager::remove_state(StateType l_state){
    m_to_be_removed_states.emplace_back(l_state);
}
void StateManager::late_update() {
    while(m_to_be_removed_states.begin() != m_to_be_removed_states.end()){
        erase_state(*m_to_be_removed_states.begin());
        m_to_be_removed_states.erase(m_to_be_removed_states.begin());
    }
}
void StateManager::erase_state(StateType l_state){
    std::erase_if(m_states, [l_state](auto& pair){
        return pair.first == l_state;
    });

}
bool StateManager::has_state(StateType l_state) {
    auto found_in_to_be_removed = std::find(m_to_be_removed_states.begin(),
                           m_to_be_removed_states.end(),
                           l_state);
    if (found_in_to_be_removed != m_to_be_removed_states.end()) {
        // treat State as not existent when it is already marked for removal!
        return false;
    }
    auto found = std::find_if(m_states.begin(),
                               m_states.end(),
                               [l_state](auto &pair) {
                                   return l_state == pair.first;
                               });
    return found != m_states.end();
}
bool StateManager::has_states() {
    return !m_states.empty();
}