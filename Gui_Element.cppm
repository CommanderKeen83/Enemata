//
// Created by CommanderKeen on 14.02.25.
//
module;
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <sstream>
#include <vector>
#include <memory>

export module SharedState:Gui_Element;

// Base Class for Gui
export class Gui_Element{
public:
    Gui_Element() = default;
    // Delete copy constructor and copy assignment
    Gui_Element(const Gui_Element&) = delete;
    Gui_Element& operator=(const Gui_Element&) = delete;

    // Default move constructor and move assignment
    Gui_Element(Gui_Element&&) = default;
    Gui_Element& operator=(Gui_Element&&) = default;

    virtual ~Gui_Element() = default;
    virtual void read_in(std::stringstream& l_ss) = 0;
    virtual void on_click(const sf::Vector2f& l_mousePos = {0,0}) = 0;
    virtual bool handleEvent(const sf::Event& l_event) = 0;
    virtual void update(const float& l_dt) = 0;
    virtual void draw(sf::RenderTarget* l_render_target) = 0;
    virtual void setSize(const sf::Vector2f l_size) {
        m_size = l_size;
    }
    virtual void setPosition(const sf::Vector2f l_position) {
        m_position = l_position;
    }
    virtual sf::FloatRect getBounds() const {
        return {m_position, m_size};
    }
    virtual bool contains(const sf::Vector2f& l_point) {
        return getBounds().contains(l_point);
    }
    // might be useful in the future for Focus Management
    virtual void on_release() = 0;
    virtual void on_hover(const sf::Vector2f& l_mousePos) = 0;
    virtual void on_leave() = 0;
protected:
    Gui_Element* m_parent = nullptr;
    std::vector<std::unique_ptr<Gui_Element>> m_children;
    sf::Vector2f m_size, m_position;
    bool m_visible = true;
    bool m_enabled = true;
};
