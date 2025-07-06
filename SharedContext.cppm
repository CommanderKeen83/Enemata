//
// Created by CommanderKeen on 10.11.24.
//



export module SharedState:SharedContext;


export class Window;
export class EventManager;
export class StateManager;
export class Gui_Manager;
export class TextureManager;

export struct SharedContext{
    Window* m_window = nullptr;
    EventManager* m_eventManager = nullptr;
    StateManager* m_stateManager = nullptr;
    Gui_Manager* m_guiManager = nullptr;
};




