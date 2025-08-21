//
// Created by SF on 02.08.25.
//
module;
#include <string>
module SharedState;
import :TextureManager;
Map::Map(TextureManager* l_texture_manager, const std::string& l_default_tile_sheet_texturename) {
    l_texture_manager->loadResource(l_default_tile_sheet_texturename);
}

void Map::load_map(const std::string& l_map_name) {

}
