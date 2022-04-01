//
// Created by Keen on 23/10/2021.
//

#include "BaseState.hpp"
#include "StateManager.hpp"
#include "Window.hpp"
BaseState::BaseState(StateManager *l_stateManager)
: m_view(l_stateManager->getContext()->m_window->getRenderWindow()->getDefaultView())
, m_stateManager(l_stateManager){

}
