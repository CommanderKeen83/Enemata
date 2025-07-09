//
// Created by SF on 03.07.25.
//
module;
#include <SFML/Graphics/Texture.hpp>

export module SharedState:TextureManager;
import :ResourceManager;
import Logger;


export class TextureManager final : public ResourceManager<TextureManager,sf::Texture> {
public:
    TextureManager() : ResourceManager("Textures.config"){}
    ~TextureManager() override = default;

    std::unique_ptr<sf::Texture> load(const std::string_view l_id) {
        std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
        if (!texture->loadFromFile(l_id)) {
            Logger::getInstance().log("Error in TextureManager::load: could not open " + std::string(l_id));
            throw std::runtime_error("Error in TextureManager::load: could not open " + std::string(l_id));
        }
        Logger::getInstance().log("TextureMaanger:load: loaded texture: " + std::string(l_id));
        return texture;
    }
};


