//
// Created by SF on 28.06.25.
//
module;
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <sstream>

module SharedState;
Slider::Slider(sf::Vector2f l_size)
    : Gui_Element() {
}
void Slider::read_in(std::stringstream& l_ss) { }
void Slider::on_click(const sf::Vector2f& l_mousePos) { }
bool Slider::handleEvent(const sf::Event& l_event) {
    return false;
}
void Slider::update(const float& l_dt) { }
void Slider::draw(sf::RenderTarget* l_render_target) { }