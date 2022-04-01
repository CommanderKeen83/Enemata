//
// Created by Keen on 30/10/2021.
//

#include "GUI_Element.hpp"


GUI_Element::GUI_Element(const std::string& l_name, GUI_Element_Type l_guiElementType, GUI_Interface *l_owner)
: m_name(l_name), m_position(), m_guiElementType(l_guiElementType){

}
