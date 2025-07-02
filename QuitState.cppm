//
// Created by SF on 01.07.25.
//

export module SharedState:QuitState;

import :SharedContext;
import :BaseState;

export class QuitState : public BaseState{
public:

        explicit QuitState(SharedContext* l_context);
        ~QuitState() override;
private:
        void on_create() override;
        void on_activate() override;
        void on_deactivate() override;
        void on_destroy() override;

        virtual void update(float l_dt) override;
        virtual void draw() override;
};


