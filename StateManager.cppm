//
// Created by CommanderKeen on 10.11.24.
//

module;
#include <memory>
#include <vector>
#include <functional>
#include <string>
#include <unordered_map>
#include <optional>
export module SharedState:StateManager;

import :BaseState;
import :Types;
import :SharedContext;

enum class Command{
    SwitchTo,
    Remove,
    ClearAll
};
using Commands = std::vector<std::pair<Command, StateType>>;
using States = std::vector<std::pair<StateType, std::unique_ptr<BaseState>>>;
using StateFactory = std::unordered_map<StateType, std::function<std::unique_ptr<BaseState>()>>;
export class StateManager{
public:
    explicit StateManager(SharedContext* l_context);

    void update(const float l_dt);
    /**
     * late_update wraps up all "internal housekeeping tasks" of StateManager,
     * such as removing all for removal pending States. late_update() should be called after
     * the update() member function.
     */
    void late_update();
    void draw();
    void switch_state(StateType l_new_state);
    void remove_state(StateType l_state);
    void clear();
    bool has_state(StateType _l_state);
    bool has_states();
    std::optional<std::string> get_current_state_name();
    void print_states_to_console();


    template<typename T>
    void register_state(StateType l_state){
        m_state_factory[l_state] = [this]() {
            return std::make_unique<T>(m_shared_context);
        };
    }
private:
    void erase_state(StateType l_state);
    void switch_to(StateType l_new_state);
    void create_state(StateType l_new_state);


    States          m_states;
    Commands        m_commands;
    StateFactory    m_state_factory;
    std::vector<StateType> m_to_be_removed_states;
    SharedContext*  m_shared_context;
};