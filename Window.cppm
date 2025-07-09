//
// Created by CommanderKeen on 06.10.24.
//
module;
#include <SFML/Graphics/RenderWindow.hpp>

export module SharedState:Window;

import :EventManager;
import :EventDetails;

export class Window{
public:
    Window();
    ~Window();

    void clear(sf::Color l_color = sf::Color::Blue);
    void display();
    sf::RenderWindow* getRenderWindow();
    void update(float l_dt);
    bool isOpen();
    EventManager* getEventManager();
private:
    void createWindow();
    void toggleFullscreen(EventDetails* l_details);
    void closeWindow(EventDetails* = nullptr);

    sf::RenderWindow            m_renderWindow;
    EventManager                m_eventManager;
    sf::Vector2u                m_windowSize;
    bool                        m_isOpen;
    bool                        m_isFullscreen;
};