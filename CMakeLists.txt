cmake_minimum_required(VERSION 3.0)
project(enemata)
find_package(SFML COMPONENTS system graphics)
set(SOURCES
        GUI/Button.cpp
        GUI/Button.hpp
        GUI/GUI_Element.cpp
        GUI/GUI_Element.hpp
        GUI/GUI_Event.hpp
        GUI/GUI_Interface.cpp
        GUI/GUI_Interface.hpp
        GUI/GUI_Label.cpp
        GUI/GUI_Label.hpp
        GUI/GUI_Manager.cpp
        GUI/GUI_Manager.hpp
        GUI/GUI_Style.cpp
        GUI/GUI_Style.hpp
        Application.cpp
        Application.hpp
        BaseState.cpp
        BaseState.hpp
        EventManager.cpp
        EventManager.hpp
        GameState.cpp
        GameState.hpp
        Logger.cpp
        Logger.hpp
        main.cpp
        MenuState.cpp
        MenuState.hpp
        OptionState.cpp
        OptionState.hpp
        PauseState.cpp
        PauseState.hpp
        README.md
        ResourceManager.hpp
        SharedContext.hpp
        StateManager.cpp
        StateManager.hpp
        TextureManager.cpp
        TextureManager.hpp
        Utils.hpp
        Window.cpp
        Window.hpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} sfml-system sfml-graphics)