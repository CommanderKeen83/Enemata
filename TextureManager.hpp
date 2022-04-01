//
// Created by Keen on 13/11/2021.
//

#ifndef ENEMATA_TEXTUREMANAGER_HPP
#define ENEMATA_TEXTUREMANAGER_HPP

#include "ResourceManager.hpp"
#include <SFML/Graphics/Texture.hpp>

class TextureManager : public ResourceManager<sf::Texture, TextureManager>{
friend ResourceManager;
public:
    TextureManager();
private:
    std::unique_ptr<sf::Texture> loadImplementation(const std::string& l_resourcePath);

};


#endif //ENEMATA_TEXTUREMANAGER_HPP
