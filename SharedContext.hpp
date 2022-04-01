//
// Created by Keen on 28/10/2021.
//

#ifndef ENEMATA_SHAREDCONTEXT_HPP
#define ENEMATA_SHAREDCONTEXT_HPP

class Window;
class EventManager;
class TextureManager;
class GUI_Manager;
struct SharedContext{
    Window* m_window = nullptr;
    EventManager* m_eventManager = nullptr;
    TextureManager* m_textureManager = nullptr;
    GUI_Manager* m_gui_manager = nullptr;
};
#endif //ENEMATA_SHAREDCONTEXT_HPP
