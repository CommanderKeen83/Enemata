//
// Created by CommanderKeen on 09.11.24.
//

export module SharedState:Types;

export enum class StateType{
    Global,
    Menu,
    Game,
    Pause,
    Exit
};

export enum class Gui_Element_Type{
    None = -1, Window, Interface, Button, Label, Scrollbar, Textfield
};
