//
// Created by SF on 01.07.25.

module;
#include <vector>
#include <memory>
#include <SFML/Graphics/Font.hpp>

export module SharedState:QuitState;

import :SharedContext;
import :BaseState;
import :Button;
import :Gui_Element;
import :Label;
import :Gui_Container;

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
        void setupGui();

    void arrow_key_left(EventDetails* l_details);
    void arrow_key_right(EventDetails* l_details);
    void select(EventDetails* l_details = nullptr);

    std::unique_ptr<Gui_Container>          m_gui_container;
    sf::Font                                m_font;
    int                                     m_selected_button = 0; // Label sits on position 0 in m_gui_elements
};


