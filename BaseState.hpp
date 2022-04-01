//
// Created by Keen on 23/10/2021.
//

#ifndef ENEMATA_BASESTATE_HPP
#define ENEMATA_BASESTATE_HPP

#include <SFML/Graphics/View.hpp>

class StateManager;

class BaseState {
public:
    explicit BaseState(StateManager* l_stateManager);
    virtual ~BaseState() = default;
    virtual void initialize() = 0;
    virtual void activate() = 0;
    virtual void deActivate() = 0;
    virtual void destroy() = 0;

    virtual void update() = 0;
    virtual void draw() = 0;
protected:
    sf::View                m_view;
    StateManager*           m_stateManager;
};


#endif //ENEMATA_BASESTATE_HPP
