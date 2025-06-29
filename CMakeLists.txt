cmake_minimum_required(VERSION 3.28)
project(ConsoleEnemata)

# Set sources first
set(SOURCES main.cpp
        Window.cpp
        EventManager.cpp
        StateManager.cpp
        MenuState.cpp
        GameState.cpp
        Gui_Manager.cpp
        Gui_Element.cpp
        Button.cpp
        Label.cpp
        Slider.cpp
        TextBox.cpp

)

# Configure SFML (try static first, comment out if you want shared)
set(SFML_STATIC_LIBRARIES ON)

# Find SFML packages before creating executable
find_package(SFML COMPONENTS System Graphics REQUIRED)

# Create executable
add_executable(ConsoleEnemata ${SOURCES})

# Set C++ standard and enable modules
target_compile_features(ConsoleEnemata PRIVATE cxx_std_26)

# Enable C++26 modules support for Clang

# Set module compilation properties
set_target_properties(ConsoleEnemata PROPERTIES
        CXX_SCAN_FOR_MODULES ON
)

# Add module sources
target_sources(ConsoleEnemata
        PUBLIC
        FILE_SET CXX_MODULES FILES
        Window.cppm
        Game.cppm
        StateManager.cppm
        SharedState.cppm
        SharedContext.cppm
        Types.cppm
        EventType.cppm
        EventInfo.cppm
        EventDetails.cppm
        EventBinding.cppm
        EventManager.cppm
        BaseState.cppm
        MenuState.cppm
        GameState.cppm
        Utils.cppm
        Logger.cppm
        Gui_Manager.cppm
        Gui_Element.cppm
        Gui_Style.cppm
        Button.cppm
        Label.cppm
        Slider.cppm
        TextBox.cppm

)

# Link external libraries
target_link_libraries(ConsoleEnemata
        SFML::Graphics)