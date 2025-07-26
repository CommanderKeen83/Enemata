//
// Created by CommanderKeen on 07.10.24.
//
module;
#include <SFML/Graphics/RenderWindow.hpp>

module SharedState;
import :Types;

Window::Window()
:   m_renderWindow{},
    m_windowSize{800, 600},
    m_isOpen{true},
    m_isFullscreen{false}
{
    createWindow();
    m_eventManager.registerCallback(StateType::Global,
                                    "CloseX",
                                    &Window::closeWindow,
                                    this);
    m_eventManager.registerCallback(StateType::Global,
                                    "FullScreen",
                                    &Window::toggleFullscreen,
                                    this);
}
Window::~Window() {
    m_renderWindow.close();
}
sf::RenderWindow* Window::getRenderWindow(){
    return &m_renderWindow;
}
EventManager* Window::getEventManager(){
    return &m_eventManager;
}
void Window::closeWindow(EventDetails* l_details){
    m_isOpen = false;
}
void Window::update(float l_dt) {
    while (const std::optional<sf::Event> event = m_renderWindow.pollEvent()){
        m_eventManager.handleEvents(event.value());
        if (event->is<sf::Event::Closed>()){
            m_isOpen = false;
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                m_isOpen = false;
        }
    }
    m_eventManager.update(l_dt);
}
bool Window::isOpen(){
    return m_isOpen;
}
void Window::createWindow() {
    m_renderWindow.close();

    m_renderWindow.create(sf::VideoMode{m_windowSize}, "Enemata");
}
void Window::toggleFullscreen(EventDetails* l_details) {
    m_renderWindow.close();
    sf::State display_mode = m_isFullscreen ? sf::State::Windowed : sf::State::Fullscreen;
    m_isFullscreen = !m_isFullscreen;
    m_renderWindow.create(sf::VideoMode{m_windowSize}, "Enemata", display_mode);
}
void Window::clear(sf::Color l_color) {
    m_renderWindow.clear(l_color);
}
void Window::display() {
    m_renderWindow.display();
}