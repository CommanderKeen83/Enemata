//
// Created by CommanderKeen on 10.11.24.
//

module;
#include <unordered_map>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <SFML/Window/Event.hpp>

module SharedState;

import :Types;
import Logger;
import Utils;

void EventManager::setCurrentState(StateType l_stateType){
    m_currentStateType = l_stateType;
    Logger::getInstance().log("EventManager::setCurrentState: set to " + std::to_string(int(l_stateType)));
}

void EventManager::removeCallback(StateType l_stateType, const std::string& l_name){
    auto found_callbackContainer = m_callbacks.find(l_stateType);
    if(found_callbackContainer == m_callbacks.end()){
        std::string error_message = "Warning in EventManager::removeCallbacks - removeCallback(...) was invoked, but passed StateType not found in m_callbacks.";
        std::cout << error_message;
        Logger::getInstance().log(error_message);
        return;
    }
    auto found_callback = found_callbackContainer->second.find(l_name);
    if(found_callback == found_callbackContainer->second.end()){
        std::string error_message = "Warning in EventManager::removeCallbacks - removeCallback(...) was invoked, but passed callback " + l_name + " was not found.";
        std::cout << error_message;
        Logger::getInstance().log(error_message);
        return;
    }
    found_callbackContainer->second.erase(found_callback);
    Logger::getInstance().log("EventManager::removeCallbacks - removed Callback " + l_name);
}

void EventManager::handleEvents(const sf::Event& l_event){
    //check all bindings against occured event
    for(auto& binding_pair : m_bindings){
        for(const auto& binding : binding_pair.second.m_event_bindings){
            EventType SFML_event = convert_SFMLEventtype_to_EventType(l_event);
            if(SFML_event != binding.first){
                // maybe the passed SFML-event fits to another EventType/EventInfo Pair of this Binding, so move to next one
                continue;
            }
            // from here we have a match! for some special events we need to store extra data which is handled here
            if(SFML_event == EventType::KeyPressed || SFML_event == EventType::KeyReleased) {
                sf::Keyboard::Key sfml_key = sf::Keyboard::Key::Unknown;
                const auto* keyPressed = l_event.getIf<sf::Event::KeyPressed>();
                if (keyPressed) {
                    sfml_key = keyPressed->code;
                }
                const auto* keyReleased = l_event.getIf<sf::Event::KeyReleased>();
                if (keyReleased) {
                    sfml_key = keyReleased->code;
                }
                // we only know that e KeyPressed / KeyReleased Event occured but we do not know if
                // it maches the stored Keyboard::Key, so we need to check that too

                if (std::get<sf::Keyboard::Key>(binding.second.m_code) == sfml_key) {
                    binding_pair.second.m_event_details.m_key = sfml_key;
                    binding_pair.second.m_triggered_event_count++;
                }
            }
            else if(SFML_event == EventType::MouseButtonPressed || SFML_event == EventType::MouseButtonReleased){
                sf::Mouse::Button sfml_mousebutton;
                const auto* mouse_button_pressed = l_event.getIf<sf::Event::MouseButtonPressed>();
                if(mouse_button_pressed){
                    sfml_mousebutton = mouse_button_pressed->button;
                }
                const auto* mouse_button_released = l_event.getIf<sf::Event::MouseButtonReleased>();
                if(mouse_button_released){
                    sfml_mousebutton = mouse_button_released->button;
                }
                if(std::get<sf::Mouse::Button>(binding.second.m_code) == sfml_mousebutton){
                    binding_pair.second.m_event_details.m_button = sfml_mousebutton;
                    binding_pair.second.m_triggered_event_count++;
                }
            }
            else {
                // since we had a sfml-event-match but nothing particular to save, we just acknowledge the match
                binding_pair.second.m_triggered_event_count++;
            }
        }
    }
}
void EventManager::update(float l_dt){
    for(auto& binding_pair : m_bindings){
        for(auto& binding : binding_pair.second.m_event_bindings){

            if(binding.first == EventType::RealTimeKeyboard){
                if(sf::Keyboard::isKeyPressed(std::get<sf::Keyboard::Key>(binding.second.m_code))){
                    binding_pair.second.m_event_details.m_key = std::get<sf::Keyboard::Key>(binding.second.m_code);
                    binding_pair.second.m_triggered_event_count++;
                }
            }
        }
        // TODO: when all bindings from a binding have been triggered, we fire the action associated with the binding!
        if(binding_pair.second.m_event_bindings.size() == binding_pair.second.m_triggered_event_count){
            auto globalCallbacks = m_callbacks.find(StateType::Global);
            if(globalCallbacks != m_callbacks.end()){
                auto callback = globalCallbacks->second.find(binding_pair.first);
                if(callback != globalCallbacks->second.end()){
                    // global Callback gets invoked
                    callback->second(&binding_pair.second.m_event_details);
                }
            }
            // from here: local Callbacks specific to current State
            auto localCallbacks = m_callbacks.find(m_currentStateType);
            if(localCallbacks != m_callbacks.end()){
                auto callback = localCallbacks->second.find(binding_pair.first);
                if(callback != localCallbacks->second.end()){
                    // global Callback gets invoked
                    callback->second(&binding_pair.second.m_event_details);
                    Logger::getInstance().log("callback for binding " + binding_pair.second.m_name + " activated");
                    std::cout << "callback for binding " + binding_pair.second.m_name + " activated\n";
                }
            }
        }
        // delete counter of current binding because all of his sub-bindings have been processed!
        binding_pair.second.m_event_details.clear();
        binding_pair.second.m_triggered_event_count = 0;
    }

}
void EventManager::loadBindings(){
    std::ifstream file;
    std::string filePath = Utils::get_project_path() + "/resources/config/keys.config";
    filePath = Utils::formatPath(filePath);

    Logger::getInstance().log("full file path for loading bindings: " + filePath);

    file.open(filePath);
    if (!file.is_open()) {
        std::string errorMessage{ "Error in EventManager::load_bindings_from_file() - could not open " + filePath };
        Logger::getInstance().log(errorMessage);
        throw std::runtime_error(errorMessage);
    }
    std::string line{};
    while (std::getline(file, line)) {
        if (line.length() < 2) { continue; } //if entry is so short, something is wrong anyway, thus skip the line
        if (line[0] == '#' || (line[0] == '\\' && line[1] == '\\')) { continue; }

        std::stringstream ss{line};
        std::string binding_name{};
        // first entry in line is always the name of the binding that holds all entries
        ss >> binding_name;
        EventBinding binding{binding_name};

        std::string segment;
        while(ss >> segment){
            std::stringstream segment_ss{segment};
            std::string token_from_segment{};
            std::vector<std::string> entries;
            while(std::getline(segment_ss, token_from_segment, ':')){
                entries.emplace_back(token_from_segment);
            }
            if(entries.empty()){
                throw std::runtime_error("Error in EventManager::loadbindings: No \":\" separator in keys.config");
            }

            switch(entries.size()){
                // only one entry
                case(1): {
                    binding.add_event_pair(get_EventType_from_string(entries[0]), EventInfo{});
                    break;
                }
                case(2): {
                    binding.add_event_pair(get_EventType_from_string(entries[0]),
                                           EventInfo{get_input_from_string(entries[1])});
                    break;
                }
                case(3): {
                    break;
                }
                case(4): {
                    break;
                }
                default: {
                    std::string error_message = "Error in EventManager::loadBindings: Config Entity is only allowed to have 2 to 4 Entries;";
                    error_message.append("Current Config Entity \"" + entries.front() + "\" has " + std::to_string(entries.size()) + " entries");
                    throw std::runtime_error(error_message);
                }
            }
        } // end of while(ss >> segment) {...}
        m_bindings.emplace(binding.m_name, binding);
    } // end of while(std::getline(file, line))...
    file.close();
}
