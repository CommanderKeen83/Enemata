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

export module SharedState:TextBox;
import :Gui_Element;
export class TextBox : public Gui_Element{
public:
    TextBox(sf::Vector2f l_size = {150, 110});
    virtual void read_in(std::stringstream& l_ss) override;
    virtual void on_click(const sf::Vector2f& l_mousePos) override;
    virtual bool handleEvent(const sf::Event& l_event) override;
    virtual void update(const float& l_dt) override;
    virtual void draw(sf::RenderTarget* l_render_target) override;

    // custom methods for Label
    std::string getText() const;
    void setMaxLength(int l_length);
private:
    sf::Font* m_font;
    sf::Text m_text;
    unsigned int m_max_length;
};