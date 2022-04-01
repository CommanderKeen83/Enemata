//
// Created by Keen on 08/11/2021.
//

#ifndef ENEMATA_GUI_LABEL_HPP
#define ENEMATA_GUI_LABEL_HPP

#include "GUI_Element.hpp"
class GUI_Label : public GUI_Element{
public:
    GUI_Label(const std::string& l_name, GUI_Interface* l_owner);
};


#endif //ENEMATA_GUI_LABEL_HPP
