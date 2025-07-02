//
// Created by SF on 28.06.25.
//
module;
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <sstream>

module SharedState;
Label::Label(sf::Font* l_font)
    : m_font(l_font), m_text(*l_font){
}
void Label::read_in(std::stringstream& l_ss) { }
void Label::on_click(const sf::Vector2f& l_mousePos) { }
bool Label::handleEvent(const sf::Event& l_event) {
    return false;
}
void Label::update(const float& l_dt) { }
void Label::draw(sf::RenderTarget* l_render_target) {
    l_render_target->draw(m_text);
}

void Label::setText(const std::string_view l_text) {
    m_text.setString(std::string(l_text));
}

void Label::setTextColor(const sf::Color l_color){}
void Label::setTextSize(const int l_textSize) {
    m_text.setCharacterSize(std::max(1, l_textSize));
}
void Label::on_release() {}
void Label::on_hover(const sf::Vector2f& l_mousePos){}
void Label::on_leave() {}