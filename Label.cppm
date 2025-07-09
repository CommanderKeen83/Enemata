//
// Created by SF on 28.06.25.
//
module;
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <sstream>
export module SharedState:Label;
import :Gui_Element;
export class Label : public Gui_Element {
public:
    Label(sf::Font* l_font = nullptr);
    void read_in(std::stringstream& l_ss) override;
    void on_click(const sf::Vector2f& l_mousePos) override;
    bool handleEvent(const sf::Event& l_event) override;
    void update(const float& l_dt) override;
    void on_render(sf::RenderTarget* l_render_target, const sf::Transform& l_transform) override;
    void on_release() override;
    void on_hover(const sf::Vector2f& l_mousePos) override;
    void on_leave() override;

    // custom methods for Label
    void setText(const std::string_view l_text);
    std::string getText() const;
    void setTextColor(const sf::Color l_color);
    void setTextSize(const int l_textSize);

private:
    sf::Font* m_font;
    sf::Text m_text;
};