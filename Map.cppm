
module;
#include <vector>
export module Map;

import Tiles;
export class Map {
public:
    void load_map(const std::string& l_map_name);
private:
    std::vector<TileInfo> m_tile_types; // stores all available tile blueprints loaded from /resources/Maps/TileTypes.tiles

};
