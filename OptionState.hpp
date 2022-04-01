//
// Created by Keen on 24/10/2021.
//

#ifndef ENEMATA_OPTIONSTATE_HPP
#define ENEMATA_OPTIONSTATE_HPP

#include "BaseState.hpp"
class OptionState : public BaseState{
public:
    OptionState(StateManager* l_stateManager);
    ~OptionState() override = default;

    void initialize() override;

    void activate() override;

    void deActivate() override;

    void destroy() override;

    void update() override;

    void draw() override;
};


#endif //ENEMATA_OPTIONSTATE_HPP
