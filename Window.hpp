//
// Created by Keen on 23/10/2021.
//

#ifndef ENEMATA_WINDOW_HPP
#define ENEMATA_WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "EventManager.hpp"

class Window {
public:
    Window();
    ~Window();
    inline sf::RenderWindow* getRenderWindow() { return &m_window; }
    inline EventManager* getEventManager(){ return &m_eventManager;}
    inline void clear(sf::Color l_color = sf::Color::Blue){ m_window.clear(l_color);}
    inline void display(){ m_window.display();}
    inline bool isOpen() const { return m_isOpen; }
    void handleEvents();
private:
    void close(EventDetails*);
    void toggleFullScreen(EventDetails*);
    void createWindow();
    sf::RenderWindow            m_window;
    sf::Vector2u                m_windowSize;
    EventManager                m_eventManager;
    bool                        m_isOpen;
    bool                        m_isFullScreen;
};


#endif //ENEMATA_WINDOW_HPP
