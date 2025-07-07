//
// Created by CommanderKeen on 27.11.24.
//
module;
#include <SFML/Graphics/View.hpp>

export module SharedState:BaseState;

import :SharedContext;
import :Window;
import Logger;

export class BaseState{
public:
    explicit BaseState(SharedContext* l_context)
    : m_view(l_context->m_window->getRenderWindow()->getDefaultView()),
    m_shared_context(l_context), m_is_transparent(false), m_is_transcendent(false){
        Logger::getInstance().log("BaseState::BaseState");
    }
    virtual ~BaseState() = default;

    virtual void on_create() = 0;
    virtual void on_activate() = 0;
    virtual void on_deactivate() = 0;
    virtual void on_destroy() = 0;

    virtual void update(float l_dt) = 0;
    virtual void draw() = 0;

    bool is_transparent() const { return m_is_transparent; }
    bool is_transcendent() const { return m_is_transcendent; }
    const sf::View& getView() const { return m_view; }

protected:
    sf::View m_view;
    SharedContext* m_shared_context;
    bool m_is_transparent;
    bool m_is_transcendent;
};