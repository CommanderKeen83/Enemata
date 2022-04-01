//
// Created by Keen on 23/10/2021.
//

#include "Window.hpp"
#include <SFML/Window/Event.hpp>

Window::Window()
// perfect DOS Resolution
: m_window()
, m_windowSize(640, 360) 
, m_isOpen(true)
, m_isFullScreen(false){
    createWindow();
    m_eventManager.addCallback(StateType::Global, "closeWindowX", &Window::close, this);
    m_eventManager.addCallback(StateType::Global, "closeShortCut", &Window::close, this);
    m_eventManager.addCallback(StateType::Global, "fullscreen", &Window::toggleFullScreen, this);
}

Window::~Window() {
    m_window.close();
}

void Window::handleEvents() {
    sf::Event event;
    while(m_window.pollEvent(event)){
        m_eventManager.handleEvents(event);
    }
    m_eventManager.update();
}

void Window::close(EventDetails *) {
    m_isOpen = false;
}

void Window::toggleFullScreen(EventDetails *) {
    m_isFullScreen = !m_isFullScreen;
    createWindow();
}

void Window::createWindow() {
    int style = m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default;
    sf::View view{{0,0, float(m_windowSize.x), float(m_windowSize.y)}};
    if(m_window.isOpen()){
        view = m_window.getView();
    }
    m_window.create({m_windowSize.x, m_windowSize.y}, "enemata", style);
    m_window.setView(view);
}
