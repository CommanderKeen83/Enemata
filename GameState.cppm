//
// Created by CommanderKeen on 13.02.25.
//

module;


export module SharedState:GameState;

import :BaseState;
import :SharedContext;

export class GameState : public BaseState{
public:
    explicit GameState(SharedContext* l_context);

private:
    void on_create() override;
    void on_activate() override;
    void on_deactivate() override;
    void on_destroy() override;
    void switch_to_Menu();

    void update(float l_dt) override;
    void draw() override;
};
