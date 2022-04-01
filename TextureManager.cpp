//
// Created by Keen on 13/11/2021.
//

#include "TextureManager.hpp"
#include <stdexcept>
TextureManager::TextureManager()
: ResourceManager<sf::Texture, TextureManager>(R"(../resources/configuration/textures.cfg)"){

}

std::unique_ptr<sf::Texture> TextureManager::loadImplementation(const std::string &l_resourcePath) {
    auto texture = std::make_unique<sf::Texture>();
    if(!texture->loadFromFile(l_resourcePath)){
        throw std::runtime_error("Errror in TextureManager::loadImplementation: could not open \""
        + l_resourcePath + "\" ...file missing?");
    }
    return std::move(texture);
}
