//
// Created by Keen on 30/10/2021.
//

#include "GUI_Element.hpp"


GUI_Element::GUI_Element(const std::string& l_name, GUI_Element_Type l_guiElementType, GUI_Interface* l_owner)
:
m_visual()
, m_styles()
, m_name(l_name)
, m_position(), m_guiElementType(l_guiElementType)
, m_currentElementState(GUI_Element_State::Neutral)
, m_owner(l_owner)
, m_isActive(true)
, m_needsRedraw(false)
, m_hasControl(false)
{

}

void GUI_Element::updateStyle(const GUI_Element_State &l_GUI_elementState, const GUI_Style &l_gui_style) {

}

void GUI_Element::applyStyle() {

}
