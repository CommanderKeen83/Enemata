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
    : m_text(*l_font) {
    set_selectable(true);
}

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
void Button::on_render(sf::RenderTarget* l_render_target, const sf::Transform& l_transform){
    sf::RenderStates state;
    state.transform = l_transform;
    l_render_target->draw(m_text, state);
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

void Button::set_text_fill_color(const sf::Color l_color) {
    m_text.setFillColor(l_color);
}
void Button::setTextSize(const int l_textSize) {
    m_text.setCharacterSize(std::max(1, l_textSize));
}
void Button::setCallback(std::function<void()>&& l_callback) {
    m_callback = l_callback;
}
void Button::set_selected(bool l_selected) {
    Gui_Element::set_selected(l_selected);
    if (isSelected()) {
        m_text.setFillColor(m_selectedColor);
    }else {
        m_text.setFillColor(m_unSelectedColor);
    }
}

void Button::setSelectedColor(sf::Color l_color){
    m_selectedColor = l_color;
}
void Button::setUnSelectedColor(sf::Color l_color){
    m_unSelectedColor = l_color;
}