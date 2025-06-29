//
// Created by SF on 28.06.25.
//
module;
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <sstream>
export module SharedState:Label;
import :Gui_Element;
export class Label : public Gui_Element {
public:
    Label(sf::Vector2f l_size = {100, 60});
    virtual void read_in(std::stringstream& l_ss) override;
    virtual void on_click(const sf::Vector2f& l_mousePos) override;
    virtual bool handleEvent(const sf::Event& l_event) override;
    virtual void update(const float& l_dt) override;
    virtual void draw(sf::RenderTarget* l_render_target) override;

    // custom methods for Label
    void setText(const std::string_view l_text);
    std::string getText() const;
    void setTextColor(const sf::Color l_color);
    void setTextSize(const int l_textSize);

private:
    sf::Font* m_font;
    sf::Text m_text;
};