//
// Created by Keen on 23/10/2021.
//

#include "Application.hpp"

Application::Application()
: m_window(), m_guiManager(), m_stateManager(&m_sharedContext), m_sharedContext(), m_textureManager(){
    m_sharedContext.m_window = &m_window;
    m_sharedContext.m_eventManager = m_window.getEventManager();
    m_sharedContext.m_textureManager = &m_textureManager;
    m_sharedContext.m_gui_manager = &m_guiManager;

    m_textureManager.loadResource("menu_background");
    m_stateManager.switchState(StateType::Menu);
}

void Application::run() {
    sf::Clock clock;
    const float fixedTimeStamp = 1.f / 60.f;
    while(m_window.isOpen()){
        float elapsed = clock.restart().asSeconds();
        if(elapsed > fixedTimeStamp){
            update(fixedTimeStamp);
        }else{
            update(elapsed);
        }
        draw();
    }
}

void Application::update(const float& l_dt) {
    m_window.handleEvents();
    GUI_Event guiEvent;
    m_stateManager.update(l_dt);
    m_guiManager.update(l_dt);

    while(m_guiManager.pollGUIEvent(guiEvent)){
        m_window.getEventManager()->handleGUIEvents(guiEvent);
    }

}

void Application::draw() {
    m_window.clear();
    m_stateManager.draw();

    sf::View currentView = m_window.getRenderWindow()->getView();
    m_window.getRenderWindow()->setView(m_window.getRenderWindow()->getDefaultView());
    m_guiManager.render(m_window.getRenderWindow());
    m_window.getRenderWindow()->setView(currentView);

    m_window.display();
}
