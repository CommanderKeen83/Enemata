module;
#include <sstream>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

export module SharedState:Gui_Container;

import :Gui_Element;

export class Gui_Container : public Gui_Element {
public:
    void read_in(std::stringstream& l_ss) override {}
    template<typename T>
    void on_click() {
        if (m_children[m_selected_item]->isSelectable()) {
            dynamic_cast<T*>(m_children[m_selected_item].get())->on_click();
        }
    }
    template<typename T>
    T* getElement(int l_index) {
        return static_cast<T*>(m_children[l_index].get());
    }
    void on_click(const sf::Vector2f& l_mousePos = {0,0}) override{}
    bool handleEvent(const sf::Event& l_event) override{ return false; }
    void update(const float& l_dt) override{}
    void select_next_selectable() {
        int old_selected = m_selected_item;
        do {
            m_selected_item = (m_selected_item + 1) % m_children.size();
        }while (!m_children[m_selected_item]->isSelectable());
        if (m_selected_item != -1) {
            m_children[old_selected]->set_selected(false);
        }
        m_children[m_selected_item]->set_selected(true);
    }
    void select_previous_selectable() {
        int old_selected = m_selected_item;
        do {
            m_selected_item = (m_selected_item - 1);
            if (m_selected_item < 0) m_selected_item = m_children.size() - 1;
        }while (!m_children[m_selected_item]->isSelectable());
        m_children[old_selected]->set_selected(false);
        m_children[m_selected_item]->set_selected(true);

    }
    void selectElementAt(int l_index) {
        if (m_selected_item != -1) {
            m_children[m_selected_item]->set_selected(false);
        }
            m_children[l_index]->set_selected(true);
    }
    void on_render(sf::RenderTarget* l_render_target, const sf::Transform& l_transform) override{}
    void on_release() override{}
    void on_hover(const sf::Vector2f& l_mousePos) override{}
    void on_leave() override{}

private:
    int m_selected_item = -1;
};