//
// Created by Keen on 28/06/2025.
//

module;
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>
#include <sstream>
#include <functional>
module SharedState;


Button::Button(sf::Font* l_font)
    : m_text(*l_font)
{}

void Button::read_in(std::stringstream& l_ss) { }
void Button::on_click(const sf::Vector2f& l_mousePos) {
    m_callback();
}
void Button::on_click() {
    m_callback();
}
bool Button::handleEvent(const sf::Event& l_event) {
    return false;
}
void Button::update(const float& l_dt) { }
void Button::draw(sf::RenderTarget* l_render_target) {
    l_render_target->draw(m_text);
}
void Button::setPosition(const sf::Vector2f l_position) {
    Gui_Element::setPosition(l_position);
    m_text.setPosition(l_position);
}
std::string Button::getText() const {
    return m_text.getString();
}
void Button::on_release() {}
void Button::on_hover(const sf::Vector2f& l_mousePos) {}
void Button::on_leave() {}


void Button::setText(const std::string_view l_text) {
    m_text.setString(std::string(l_text));
}

void Button::setTextFillColor(const sf::Color l_color) {
    m_text.setFillColor(l_color);
}
void Button::setTextSize(const int l_textSize) {
    m_text.setCharacterSize(std::max(1, l_textSize));
}
void Button::setCallback(std::function<void()>&& l_callback) {
    m_callback = l_callback;
}