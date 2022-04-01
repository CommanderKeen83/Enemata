//
// Created by Keen on 23/10/2021.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "EventManager.hpp"

EventInfo::EventInfo(int l_code) : m_eventInfo(l_code){}
EventInfo::EventInfo(GUI_Event l_guiEvent) : m_eventInfo(l_guiEvent){}

EventManager::EventManager()
: m_bindings()
, m_callbacks()
, m_currentState(StateType::Menu){
    loadKeyBindings();
}

void EventManager::handleGUIEvents(const GUI_Event &l_guiEvent) {
    for (auto &binding : m_bindings) {
        for (auto& eventPair : binding.second->m_events) {
            // If binding does not hold exclusively GUI-related EventType it is of no use here; move to next binding
            if(eventPair.first != EventType::GUI_CLICK  && eventPair.first != EventType::GUI_HOVER ||
                    eventPair.first != EventType::GUI_LEAVE && eventPair.first != EventType::GUI_RELEASE){
                break;

                // cannot compare EventType and GUI_EventType directly
            }else if(( eventPair.first == EventType::GUI_CLICK    && l_guiEvent.m_guiEventType != GUI_EventType::Click) ||
                     ( eventPair.first == EventType::GUI_HOVER    && l_guiEvent.m_guiEventType != GUI_EventType::Hover) ||
                     ( eventPair.first == EventType::GUI_RELEASE  && l_guiEvent.m_guiEventType != GUI_EventType::Release) ||
                     ( eventPair.first == EventType::GUI_LEAVE    && l_guiEvent.m_guiEventType != GUI_EventType::Leave)){
                break;
            }
            auto& guiEvent = std::get<GUI_Event>(eventPair.second.m_eventInfo);
            if(guiEvent.m_interface == l_guiEvent.m_interface &&
            guiEvent.m_element == l_guiEvent.m_element){
                binding.second->m_details.m_GUI_interface = l_guiEvent.m_interface;
                binding.second->m_details.m_GUI_element = l_guiEvent.m_element;
                binding.second->m_count++;
            }
        }
    }
}

void EventManager::handleEvents(const sf::Event &l_sfmlEvent) {
    for(auto& binding : m_bindings){
        for(auto& eventPair : binding.second->m_events){
            EventType sfmlEvent = static_cast<EventType>(l_sfmlEvent.type);

            // bindings with GUI-EventTypes wont be of any use, thus move on to next binding
            if( sfmlEvent == EventType::GUI_CLICK || sfmlEvent == EventType::GUI_RELEASE ||
                sfmlEvent == EventType::GUI_LEAVE || sfmlEvent == EventType::GUI_HOVER){ break; }
            // next eventpair still might be relevant in case we have multiple eventpairs to check, so move to next
            if(sfmlEvent != eventPair.first){ continue; }

            // from here: The provided operating-system event matches the stored event from KeyBindings.cfg
            if(eventPair.first == EventType::EVENT_KEY_PRESSED || eventPair.first == EventType::EVENT_KEY_RELEASED){
                int keyCode = std::get<int>(eventPair.second.m_eventInfo);
                if(keyCode == l_sfmlEvent.key.code){
                    if(binding.second->m_details.m_keyCode == -1){
                        binding.second->m_details.m_keyCode = keyCode;
                    }
                    binding.second->m_count++;
                }
            }else if(eventPair.first == EventType::EVENT_MOUSE_BUTTON_PRESSED ||
                     eventPair.first == EventType::EVENT_MOUSE_BUTTON_RELEASED) {
                int keyCode = std::get<int>(eventPair.second.m_eventInfo);
                if(keyCode == l_sfmlEvent.mouseButton.button){
                    if(binding.second->m_details.m_keyCode == -1){
                        binding.second->m_details.m_keyCode = keyCode;
                    }
                    //position of the mouse pointer, relative to the top of the owner window
                    binding.second->m_details.m_mousePosition.x = l_sfmlEvent.mouseButton.x;
                    binding.second->m_details.m_mousePosition.y = l_sfmlEvent.mouseButton.y;
                    binding.second->m_count++;
                }
            }else{
                if(eventPair.first == EventType::EVENT_TEXT_ENTERED){
                    binding.second->m_details.m_unicode = l_sfmlEvent.text.unicode;
                }
                // no special requirements for other events, so just raise counter to acknowledge the event-match
                binding.second->m_count++;
            }

        }
    }
}

void EventManager::update() {
    for(auto& binding : m_bindings){
        for(auto& eventPair : binding.second->m_events){
            switch(eventPair.first){
                case(EventType::EVENT_REALTIME_KEYBOARD):{
                    int keycode = std::get<int>(eventPair.second.m_eventInfo);
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keycode))){
                        if(binding.second->m_details.m_keyCode == -1){
                            binding.second->m_details.m_keyCode = keycode;
                        }
                        binding.second->m_count++;
                    }
                    break;
                }
                case(EventType::EVENT_REALTIME_JOYSTICK):{
                    break;
                }
                case(EventType::EVENT_REALTIME_MOUSE):{
                    int keycode = std::get<int>(eventPair.second.m_eventInfo);
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button(keycode))){
                        if(binding.second->m_details.m_keyCode == -1){
                            binding.second->m_details.m_keyCode = keycode;
                        }
                        binding.second->m_count++;
                    }
                    break;
                }
                default: {break;}
            }
        }
        // all eventType-EventInfo-Pairs of current binding has been invoked
        if(binding.second->m_count == binding.second->m_events.size()){
            auto globalCallback = m_callbacks[StateType::Global].find(binding.second->m_details.m_bindingName);
            if(globalCallback != m_callbacks[StateType::Global].end()){
                globalCallback->second(&binding.second->m_details);
            }
            auto localCallback = m_callbacks[m_currentState].find(binding.second->m_details.m_bindingName);
            if(localCallback != m_callbacks[m_currentState].end()){
                localCallback->second(&binding.second->m_details);
            }
        }
        binding.second->m_count = 0;
        binding.second->m_details.clear();
    }
}

void EventManager::loadKeyBindings() {
    std::ifstream file;
    std::string path{"../resources/configuration/KeyBindings.cfg"};
    file.open(path);
    if(!file.is_open()){
        throw std::runtime_error("Error in EventManager::loadKeyBindings: could not open " + path);
    }
    std::string line{};
    while(std::getline(file, line)){
        if(line.empty()) continue;
        if(line[0] == '#') continue;

        std::stringstream ss{line};
        std::string name{};
        ss >> name;
        auto binding = std::make_unique<Binding>(name);
        std::string chunk{};
        while (ss >> chunk){
            std::string firstEntry, secondEntry;
            auto firstDelimiter = chunk.find_first_of(':');
            if(firstDelimiter == chunk.npos){
                std::cout << "Warning in EventManager::loadKeyBindings: File "
                << path << " has invalid entry \"" << name << "\": " << chunk << " has no \':\'\n";
                continue;
            }
            firstEntry = chunk.substr(0, firstDelimiter);
            EventType eventType = EventType(std::stoi(firstEntry));
            // GUI Events need
            if( eventType == EventType::GUI_CLICK || eventType == EventType::GUI_HOVER ||
                eventType == EventType::GUI_LEAVE || eventType == EventType::GUI_RELEASE){
                auto lastDelimiter = chunk.find_last_of(':');
                secondEntry = chunk.substr(firstDelimiter + 1, lastDelimiter - firstDelimiter - 1);
                std::string thirdEntry = chunk.substr(lastDelimiter + 1, chunk.length() - lastDelimiter);
                GUI_Event guiEvent;
                guiEvent.m_interface = secondEntry;
                guiEvent.m_element = thirdEntry;
                binding->m_events.emplace_back(eventType, EventInfo{guiEvent});
            }
            else{
                secondEntry = chunk.substr(firstDelimiter + 1, chunk.length() - firstDelimiter);
                binding->m_events.emplace_back(eventType, EventInfo{stoi(secondEntry)});
            }
        } // end of while (ss >> chunk){
        m_bindings.emplace(name, std::move(binding));
    }
}
