
module;
#include <vector>
export module Map;

import Tiles;
export class Map {
public:

private:
    std::vector<TileInfo> m_tileset; // stores all available tile blueprints loaded from /resources/Maps/TileTypes.tiles
};
