//
// Created by Keen on 25/10/2021.
//

#include "GUI_Manager.hpp"
#include "../Logger.hpp"
#include <sstream>
#include <iostream>

GUI_Manager::GUI_Manager() {
    //TODO: Register GUI_Elements
}

void GUI_Manager::loadInterface(StateType l_state, const std::string& l_fileName, const std::string &l_interfaceName) {
    std::string path = R"(../resources/gui/interfaces/)" + l_fileName;
    std::ifstream file;
    file.open(path);
    if(!file.is_open()){
        Logger::getInstance().log("GUI_Manager::loadInterface(...): could not open file " + path);
        throw std::runtime_error("Error in GUI_Manager::loadInterface: could not load file " + path);
    }
    std::string line{};
    std::string interfaceNameFromFile;
    while(std::getline(file, line)){
        if(line.empty()){ continue;}
        if(line[0] == '#'){continue;}
        if(line[0] == '|'){continue;}

        std::stringstream ss{line};
        std::string entry{};
        while(ss >> entry){
            if(entry == "Interface"){
                std::string style{};
                ss >> interfaceNameFromFile >> style;
                if(!addInterface(l_state, interfaceNameFromFile)){
                    Logger::getInstance()
                    .log("GUI_Manager::loadInterface(...): Failed loading interface with name " + interfaceNameFromFile);
                    return;
                }
                GUI_Interface* anInterface = getInterface(l_state, interfaceNameFromFile); // Microsoft might have some compiler-specific extensions named "interface", so avoid using this name
                ss >> anInterface;
            }
            else if(entry == "Element"){

            }
        }
    }
    file.close();
}

bool GUI_Manager::addInterface(StateType l_state, const std::string &l_interfaceName) {
    // emplace returns iterator to first found pair or newly created pair if none has been found
    auto gui_interfaces = m_interfaces.emplace(l_state, GUI_Interfaces{}).first;

    std::unique_ptr<GUI_Interface> gui_interface = std::make_unique<GUI_Interface>(l_interfaceName, this);
    return gui_interfaces->second.emplace(l_interfaceName, std::move(gui_interface)).second;

}

void GUI_Manager::update(float l_dt) {

}

void GUI_Manager::render(sf::RenderWindow *l_renderWindow) {

}

GUI_Element_Type GUI_Manager::convertStringToGUI_ElementType(const std::string &l_str) {
    auto foundType = m_elementTypes.find(l_str);
    return  foundType != m_elementTypes.end() ? foundType->second : GUI_Element_Type::None;
}

GUI_Interface *GUI_Manager::getInterface(StateType l_state, const std::string &l_name) {
    auto interfaces = m_interfaces.find(l_state);
    if(interfaces == m_interfaces.end()){
        return nullptr;
    }
    auto interface = interfaces->second.find(l_name);
    return interface != interfaces->second.end() ? interface->second.get() : nullptr;
}
