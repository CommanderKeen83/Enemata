//
// Created by CommanderKeen on 13.02.25.
//

module;
#include <memory>

export module SharedState:GameState;

import :BaseState;
import :SharedContext;
import Map;

export class GameState : public BaseState{
public:
    explicit GameState(SharedContext* l_context);
    ~GameState() override;

private:
    void on_create() override;
    void on_activate() override;
    void on_deactivate() override;
    void on_destroy() override;
    void switch_to_Menu();

    void update(float l_dt) override;
    void draw() override;
    std::unique_ptr<Map> m_map = nullptr;
};
