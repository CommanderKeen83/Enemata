//
// Created by Keen on 28/06/2025.
//

module;
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <sstream>
module SharedState;


TextBox::TextBox(sf::Vector2f l_size)
: Gui_Element()
{}

void TextBox::read_in(std::stringstream& l_ss) { }
void TextBox::on_click(const sf::Vector2f& l_mousePos) { }
bool TextBox::handleEvent(const sf::Event& l_event) {
    return false;
}
void TextBox::update(const float& l_dt) { }
void TextBox::draw(sf::RenderTarget* l_render_target) { }