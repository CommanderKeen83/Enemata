//
// Created by CommanderKeen on 14.10.24.
//
module;
#include <vector>
#include <string>
export module SharedState:EventBinding;

import :EventInfo;
import :EventType;
import :EventDetails;




export struct EventBinding{
    EventBinding(std::string l_name)
    : m_name (l_name),
    m_event_bindings(),
    m_event_details(),
    m_triggered_event_count(0){}
    EventBinding() : EventBinding(""){}
    ~EventBinding() = default;
    void add_event_pair(EventType l_eventType, EventInfo l_eventInfo){
        m_event_bindings.emplace_back(std::make_pair(l_eventType, l_eventInfo));
    }

    std::string                                     m_name;
    std::vector<std::pair<EventType, EventInfo>>    m_event_bindings;
    EventDetails                                    m_event_details;
    int                                             m_triggered_event_count;

};