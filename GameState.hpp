//
// Created by Keen on 23/10/2021.
//

#ifndef ENEMATA_GAMESTATE_HPP
#define ENEMATA_GAMESTATE_HPP

#include "BaseState.hpp"
class GameState : public BaseState{
public:
    GameState(StateManager* l_stateManager);
    ~GameState() override = default;

    void initialize() override;

    void activate() override;

    void deActivate() override;

    void destroy() override;

    void update() override;

    void draw() override;
};


#endif //ENEMATA_GAMESTATE_HPP
