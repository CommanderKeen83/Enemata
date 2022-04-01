//
// Created by Keen on 25/10/2021.
//

#ifndef ENEMATA_GUI_MANAGER_HPP
#define ENEMATA_GUI_MANAGER_HPP

#include "GUI_Event.hpp"
#include "GUI_Interface.hpp"
#include "GUI_Element.hpp"
#include "../StateManager.hpp"
#include <unordered_map>
#include <memory>
                                          //name of interface   //interface
using GUI_Interfaces = std::unordered_map<std::string, std::unique_ptr<GUI_Interface>>;
// each state holds its own interfaces
using GUI_Container = std::unordered_map<StateType, GUI_Interfaces>;
// each state holds its own GUI_Events
using GUI_Events = std::unordered_map<StateType, std::vector<GUI_Event>>;
using GUI_Factory = std::unordered_map<GUI_Element_Type, std::function<std::unique_ptr<GUI_Element>(GUI_Interface*)>>;
using GUI_ElementTypes = std::unordered_map<std::string, GUI_Element_Type>;
class GUI_Manager {
public:
    GUI_Manager();
    inline bool pollGUIEvent(GUI_Event& l_guiEvent){
        auto& eventContainer = m_events[m_currentState];
        if(eventContainer.empty()){ return false; }

        l_guiEvent = eventContainer.front();
        eventContainer.erase(eventContainer.begin());
        return true;
    }
    template<typename T>
    void registerGUIElement(GUI_Element_Type l_elementType){
        m_guiFactory[l_elementType] = [](GUI_Interface* l_owner){
            return std::make_unique<T>("", l_owner);
        };

    };
    inline void setState(StateType l_state){ m_currentState = l_state; }
    inline StateType getState(StateType l_state) const { return m_currentState; }
    void loadInterface(StateType l_state, const std::string& l_fileName, const std::string& l_interfaceName);

    void update(float l_dt);
    void render(sf::RenderWindow* l_renderWindow);
private:
    // creates new interface-container if needed and new GUI_Interface-object that is pushed to
    // the GUI_Interfaces container in m_interfaces.
    bool addInterface(StateType l_state, const std::string& l_interfaceName);
    GUI_Interface* getInterface(StateType l_state, const std::string& l_name);
    GUI_Element_Type convertStringToGUI_ElementType(const std::string& l_str);

    GUI_Container           m_interfaces;
    GUI_Events              m_events;
    GUI_Factory             m_guiFactory;
    GUI_ElementTypes        m_elementTypes;
    StateType               m_currentState;
};


#endif //ENEMATA_GUI_MANAGER_HPP
