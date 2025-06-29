//
// Created by CommanderKeen on 06.10.24.
//
module;

export module Game;

import SharedState;

export class Game{
public:
    Game()
    : m_stateManager(&m_sharedContext){
        m_sharedContext.m_window = &m_window;
        m_sharedContext.m_stateManager = &m_stateManager;
        m_sharedContext.m_eventManager = m_window.getEventManager();
        m_sharedContext.m_guiManager = &m_guiManager;

        m_stateManager.switch_state(StateType::Menu);
    }
    ~Game() = default;
    void run(){
        while(m_window.isOpen() && m_stateManager.has_states()) {
            update(1.f / 60.f);
            render();
        }
    }
private:
    void update(float l_dt){
        m_window.update(l_dt);
        m_stateManager.update(l_dt);
        m_stateManager.late_update();
    }
    void render(){
        m_window.clear();

        // render here
        m_stateManager.draw();

        m_window.display();
    }
    Window m_window;
    SharedContext m_sharedContext;
    StateManager m_stateManager;
    Gui_Manager m_guiManager;

};