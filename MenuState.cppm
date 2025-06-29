//
// Created by CommanderKeen on 27.11.24.
//

module;
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
export module SharedState:MenuState;

import :BaseState;
import :SharedContext;
import :EventDetails;
import :Button;

export class MenuState : public BaseState{
public:
   explicit MenuState(SharedContext* l_context);
   ~MenuState() override;
private:
    void on_create() override;
    void on_activate() override;
    void on_deactivate() override;
    void on_destroy() override;
    void keyArrowUp(EventDetails* l_details = nullptr);
    void keyArrowDown(EventDetails* l_details = nullptr);
    void select(EventDetails* l_details = nullptr);
    virtual void update(float l_dt) override;
    virtual void draw() override;

    std::unique_ptr<sf::Texture> m_backgroundTexture;
    std::unique_ptr<sf::Sprite> m_backgroundSprite;
    std::vector<Button> m_gui_buttons;

};
