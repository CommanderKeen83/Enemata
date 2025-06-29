//
// Created by SF on 28.06.25.
//
module;
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <sstream>

module SharedState;
Label::Label(sf::Vector2f l_size)
    : Gui_Element() {
}
void Label::read_in(std::stringstream& l_ss) { }
void Label::on_click(const sf::Vector2f& l_mousePos) { }
bool Label::handleEvent(const sf::Event& l_event) {
    return false;
}
void Label::update(const float& l_dt) { }
void Label::draw(sf::RenderTarget* l_render_target) { }