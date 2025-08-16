//
// Created by CommanderKeen on 14.02.25.
//
module;
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <sstream>
#include <vector>
#include <memory>

export module SharedState:Gui_Element;

// Base Class for Gui
export class Gui_Element : public sf::Transformable{
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
    virtual void render(sf::RenderTarget* l_render_target,
        const sf::Transform& l_parent_transform = sf::Transform::Identity) {
        sf::Transform combined_transform = getTransform() * l_parent_transform;
        on_render(l_render_target, combined_transform);
        for (auto& child : m_children) {
            child->render(l_render_target, combined_transform);
        }

    }

    virtual void add_child(std::unique_ptr<Gui_Element> l_child) {
        m_children.push_back(std::move(l_child));
    }
    virtual void on_render(sf::RenderTarget* l_render_target, const sf::Transform& l_transform) = 0;
    sf::Transform get_world_transform() const {
        if (m_parent) {
            return getTransform() * m_parent->get_world_transform();
        }
        return getTransform();
    }
    sf::Vector2f get_world_position() const {
        return get_world_transform().transformPoint({0,0});
    }
    virtual sf::FloatRect getBounds() const {
        return {getPosition(), m_size};
    }
    virtual bool contains(const sf::Vector2f& l_point) {
        return getBounds().contains(l_point);
    }
    // might be useful in the future for Focus Management
    virtual void on_release() = 0;
    virtual void on_hover(const sf::Vector2f& l_mousePos) = 0;
    virtual void on_leave() = 0;
    virtual void set_selectable(bool l_can_be_selected) {
        m_selectable = l_can_be_selected;
    }
    virtual bool isSelectable() const {
        return m_selectable;
    }
    virtual bool isSelected() const {
        return m_selected;
    }
    virtual void set_selected(bool l_selected) {
        if (isSelectable()) m_selected = l_selected;
    }
protected:
    Gui_Element* m_parent = nullptr;
    std::vector<std::unique_ptr<Gui_Element>> m_children;
    sf::Vector2f m_size;
    bool m_visible = true;
    bool m_enabled = true;
    bool m_selected = false;
    bool m_selectable = false;
};
