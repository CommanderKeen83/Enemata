//
// Created by Keen on 23/10/2021.
//

#ifndef ENEMATA_STATEMANAGER_HPP
#define ENEMATA_STATEMANAGER_HPP

#include <memory>
#include <unordered_map>
#include <vector>
#include "functional"
#include "SharedContext.hpp"

#include "BaseState.hpp"

enum class StateType{
    Global = 0,
    Menu,
    Game,
    Pause,
    Options

};
using States =  std::vector<std::pair<StateType, std::unique_ptr<BaseState>>>;
using StateFactory =  std::unordered_map<StateType, std::function<std::unique_ptr<BaseState>()>>;
using StatesToRemove = std::vector<StateType>;
class StateManager {
public:
    explicit StateManager(SharedContext* l_sharedContext);
//////////////////////////////////////////////////////////
// sets found State on top of stack or
// creates new State if requested state has not been found
//////////////////////////////////////////////////////////
    void switchState(StateType l_stateType);
    void removeState(StateType l_stateType);
    bool hasState(StateType l_stateType) const;
    inline SharedContext* getContext() const { return m_sharedContext; }
    template<typename T>
    void registerState(StateType l_stateType){
        m_factory[l_stateType] = [this]()->std::unique_ptr<BaseState>{
            return std::make_unique<T>(this);
        };
    }
    void update(const float& l_dt);
    void draw();

private:
    bool create(StateType l_stateType);
    void remove(StateType l_stateType);
    States          m_states;
    StateFactory    m_factory;
    StatesToRemove  m_statesToRemove;
    SharedContext*  m_sharedContext;
};


#endif //ENEMATA_STATEMANAGER_HPP
