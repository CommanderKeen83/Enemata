//
// Created by CommanderKeen on 14.10.24.
//
module;
#include <unordered_map>
#include <functional>
#include <string>
#include <SFML/Window/Event.hpp>

export module SharedState:EventManager;

import :EventType;
import :EventInfo;
import :EventBinding;
import :EventDetails;
import :Types;

import Utils;
import Logger;



using Bindings = std::unordered_map<std::string, EventBinding>;
using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;

export class EventManager{
public:
    EventManager()
    : m_bindings(), m_callbacks(), m_currentStateType(StateType::Global){
        loadBindings();
    }
    ~EventManager() = default;

    void setCurrentState(StateType l_stateType);
    template<typename T>
    void registerCallback(StateType l_stateType, const std::string& l_name, void (T::*func)(EventDetails* ), T* l_instance){
        //bind passed member function to instance and reserve placeholder to be able to pass parameter when invoking this bound function
        auto boundFunction = std::bind(func, l_instance, std::placeholders::_1);
        if(!m_callbacks[l_stateType].emplace(l_name, boundFunction).second){
            std::string errorMessage{ "Error in EventManager::registerCallback - could not register Callback " + l_name};
            Logger::getInstance().log(errorMessage);
            throw std::runtime_error(errorMessage);
        }
        Logger::getInstance().log("EventManager::registerCallback: Registered Callback " + l_name);
    }
    void loadBindings();
    void removeCallback(StateType l_stateType, const std::string& l_name);
    void handleEvents(const sf::Event& l_event);
    void update(float l_dt);
    // Class Members
    Bindings                    m_bindings;
    Callbacks                   m_callbacks;
    StateType                   m_currentStateType;
};