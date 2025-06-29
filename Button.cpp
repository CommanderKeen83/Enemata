//
// Created by Keen on 28/06/2025.
//

module;
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <sstream>
#include <functional>
module SharedState;


Button::Button(sf::Vector2f l_size)
: Gui_Element(), m_font(nullptr), m_text(*m_font), m_callback()
{}

void Button::read_in(std::stringstream& l_ss) { }
void Button::on_click(const sf::Vector2f& l_mousePos) { }
bool Button::handleEvent(const sf::Event& l_event) {
    return false;
}
void Button::update(const float& l_dt) { }
void Button::draw(sf::RenderTarget* l_render_target) { }
std::string Button::getText() const {
    return m_text.getString();
}
void Button::setText(const std::string_view l_text) {
    m_text.setString(l_text);
}

void Button::setTextColor(const sf::Color l_color){}
void Button::setTextSize(const int l_textSize) {
    unsigned int textSize = l_textSize;
    //minimum Textsize is 1
    if (l_textSize <= 0) {
        textSize = 1;
    }
    m_text.setCharacterSize(textSize);
}
void Button::setCallback(std::function<void()>& l_callback) {
    m_callback = l_callback;
}