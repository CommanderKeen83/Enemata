//
// Created by Keen on 23/10/2021.
//

#ifndef ENEMATA_APPLICATION_HPP
#define ENEMATA_APPLICATION_HPP

#include "Window.hpp"
#include "GUI/GUI_Manager.hpp"
#include "SharedContext.hpp"
#include "TextureManager.hpp"
class Application {
public:
    Application();
    Application(const Application& l_other) = delete;
    ~Application() = default;
    Application& operator= (Application& l_other) = delete;
    void run();
private:
    void update(const float& l_dt);
    void draw();

    SharedContext       m_sharedContext;
    Window              m_window;
    GUI_Manager         m_guiManager;
    StateManager        m_stateManager;
    TextureManager      m_textureManager;
};


#endif //ENEMATA_APPLICATION_HPP
