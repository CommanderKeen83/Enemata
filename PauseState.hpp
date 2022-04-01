//
// Created by Keen on 23/10/2021.
//

#ifndef ENEMATA_PAUSESTATE_HPP
#define ENEMATA_PAUSESTATE_HPP

#include "BaseState.hpp"


class PauseState : public BaseState{
public:
    PauseState(StateManager* l_stateManager);
    ~PauseState() override = default;

    void initialize() override;

    void activate() override;

    void deActivate() override;

    void destroy() override;

    void update() override;

    void draw() override;
};


#endif //ENEMATA_PAUSESTATE_HPP
