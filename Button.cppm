//
// Created by Keen on 28/06/2025.
//

module;
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <sstream>
#include <functional>

export module SharedState:Button;
import :Gui_Element;
export class Button : public Gui_Element{
public:
    Button(sf::Font* l_font = nullptr);
    Button(const Button&) = delete;
    Button& operator=(const Button&) = delete;
    Button(Button&&) = default;
    Button& operator=(Button&&) = default;
    void read_in(std::stringstream& l_ss) override;
    void on_click(const sf::Vector2f& l_mousePos) override;
    void on_click();
    bool handleEvent(const sf::Event& l_event) override;
    void update(const float& l_dt) override;
    void on_render(sf::RenderTarget* l_render_target, const sf::Transform& l_transform) override;
    void setPosition(const sf::Vector2f l_position);
    void on_release() override;
    void on_hover(const sf::Vector2f& l_mousePos) override;
    void on_leave() override;
    void set_selected(bool l_selected) override;

    // custom methods for Button
   void setText(const std::string_view l_text);
   std::string getText() const;
    void set_text_fill_color(const sf::Color l_color);
    void setTextSize(const int l_textSize);
    void setCallback(std::function<void()>&& l_callback);
private:
    sf::Text m_text;
    std::function<void()> m_callback;
};