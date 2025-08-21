
module;
#include <vector>
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
export module SharedState:Map;

import Tiles;
import :SharedContext;
export class Map {
public:
     Map(TextureManager* l_texture_manager, const std::string& l_default_tile_sheet_texturename);
    void load_map(const std::string& l_map_name);
    void load_til_sheet(const std::string& l_til_sheet_name);
private:
    std::vector<TileInfo> m_tile_types; // stores all available tile blueprints loaded from /resources/Maps/TileTypes.tiles
    std::unique_ptr<sf::Sprite> m_tilesheet_sprite;
};
