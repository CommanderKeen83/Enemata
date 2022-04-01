//
// Created by Keen on 07/02/2022.
//

#ifndef ENEMATA_UTILS_HPP
#define ENEMATA_UTILS_HPP

#endif //ENEMATA_UTILS_HPP

#include <string>
#include <cctype>
#include <algorithm>

namespace Utils{
    void toLower(std::string& l_str){
        std::transform(l_str.begin(), l_str.end(), l_str.begin(), [](unsigned char c){
            return std::tolower(c);
        });
    }
}