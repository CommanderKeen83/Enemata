//
// Created by SF on 28.06.25.
//
module;
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <sstream>
export module SharedState:Slider;
import :Gui_Element;
export class Slider : public Gui_Element {
public:
    Slider(sf::Vector2f l_size = {100, 60});
    virtual void read_in(std::stringstream& l_ss) override;
    virtual void on_click(const sf::Vector2f& l_mousePos) override;
    virtual bool handleEvent(const sf::Event& l_event) override;
    virtual void update(const float& l_dt) override;
    void on_render(sf::RenderTarget* l_render_target, const sf::Transform& l_transform) override;
};