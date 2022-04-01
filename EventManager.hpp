//
// Created by Keen on 23/10/2021.
//

#ifndef ENEMATA_EVENTMANAGER_HPP
#define ENEMATA_EVENTMANAGER_HPP

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include <variant>
#include <iostream>
#include <SFML/Window/Event.hpp>
#include "GUI/GUI_Event.hpp"
#include "StateManager.hpp"

enum class EventType{
 EVENT_WINDOW_CLOSE = sf::Event::Closed,                        //      #0
 EVENT_KEY_PRESSED = sf::Event::KeyPressed,                     //      #5
 EVENT_KEY_RELEASED = sf::Event::KeyReleased,                   //      #6
 EVENT_MOUSE_BUTTON_PRESSED = sf::Event::MouseButtonPressed,    //      #9
 EVENT_MOUSE_BUTTON_RELEASED = sf::Event::MouseButtonReleased,  //      #10
 EVENT_TEXT_ENTERED = sf::Event::TextEntered,                   //      #4
 EVENT_REALTIME_KEYBOARD = sf::Event::Count + 1,                //      #24
 EVENT_REALTIME_MOUSE,                                          //      #25
 EVENT_REALTIME_JOYSTICK,                                       //      #26
 GUI_CLICK,                                                     //      #27
 GUI_RELEASE,                                                   //      #28
 GUI_HOVER,                                                     //      #29
 GUI_LEAVE,                                                     //      #30
};

// stores info from KeyBindings configuration file
struct EventInfo{
    explicit EventInfo(int l_code);
    explicit EventInfo(GUI_Event l_guiEvent);
    std::variant<int, GUI_Event> m_eventInfo;
};


// stores event information for later use by other classes
struct EventDetails{
    explicit EventDetails(const std::string& l_bindingName)
    : m_bindingName(l_bindingName)
    , m_GUI_interface()
    , m_GUI_element()
    , m_mousePosition()
    , m_unicode()
    , m_keyCode(){
        clear();
    }

    inline void clear(){
        // DON'T clear m_bindingName!
        m_mousePosition = sf::Vector2f{};
        m_GUI_interface = "";
        m_GUI_element = "";
        m_unicode = 0;
        m_keyCode = -1;

    }
    std::string         m_bindingName;
    std::string         m_GUI_interface;
    std::string         m_GUI_element;
    sf::Vector2f        m_mousePosition;
    sf::Uint32          m_unicode;
    int                 m_keyCode;
};


struct Binding{
    explicit Binding(const std::string l_name): m_details(l_name), m_count(0), m_events(){

    }
    inline void addEventPair(EventType l_eventType, EventInfo l_eventInfo){
        m_events.emplace_back(l_eventType, l_eventInfo);
    }
    inline void clear(){ m_events.clear();}

    EventDetails                                    m_details;
    int                                             m_count;
    std::vector<std::pair<EventType, EventInfo>>    m_events;
};
using Bindings = std::unordered_map<std::string, std::unique_ptr<Binding>>;
using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;
class EventManager {
public:
    EventManager();
    template<typename T>
    void addCallback(StateType l_stateType,
                     const std::string& l_bindingName,
                     void (T::*function)(EventDetails*),
                     T* l_instance){
        std::function<void(EventDetails*)> func = std::bind(function, l_instance, std::placeholders::_1);
        if(!m_callbacks[l_stateType].emplace(l_bindingName, func).second){
            std::cout << "Warning in EventManager::addCallback: could not add callback " << l_bindingName
            << " for StateType " << int(l_stateType) <<"\n";
        }
    }
    inline void removeCallback(StateType l_stateType, const std::string& l_bindingName){
        auto foundCallbackContainer = m_callbacks.find(l_stateType);
        if(foundCallbackContainer == m_callbacks.end()){
            std::cout << "Warning in EventManager::removeCallback: could not find StateType "
            << int(l_stateType) << "\n";
            return;
        }
        auto foundCallback = foundCallbackContainer->second.find(l_bindingName);
        if(foundCallback == foundCallbackContainer->second.end()){
            std::cout << "Warning in EventManager::removeCallback: could not find Binding "
                      << l_bindingName << " in Callback-Container for StateType " << int(l_stateType) << "\n";
            return;
        }
        foundCallbackContainer->second.erase(foundCallback);
    }
    inline void setState(StateType l_state){ m_currentState = l_state; }
    void handleGUIEvents(const GUI_Event& l_guiEvent);
    void handleEvents(const sf::Event& l_sfmlEvent);
    void update();

private:
    void                loadKeyBindings();
    Bindings            m_bindings;
    Callbacks           m_callbacks;
    StateType           m_currentState;
};


#endif //ENEMATA_EVENTMANAGER_HPP
