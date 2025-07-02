//
// Created by CommanderKeen on 09.11.24.
//
module;
#include <string>
export module SharedState:Types;

export enum class StateType{
    None,
    Global,
    Menu,
    Game,
    Pause,
    Quit,
};

export std::string StateType_to_String(StateType l_type){
    switch(l_type){
        case (StateType::Game): return "Game";
        case (StateType::Menu): return "Menu";
        case (StateType::Pause): return "Pause";
        case (StateType::Quit): return "Quit";
        default: return "No StateType found";
    }
}

export enum class Gui_Element_Type{
    None = -1, Window, Interface, Button, Label, Scrollbar, Textfield
};
