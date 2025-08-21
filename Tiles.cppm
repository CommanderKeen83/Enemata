module;

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Context.hpp>
#include <string>
export module Tiles;

import Utils;

export enum class TileType {
    Unknown = -1,
    HighGrassWalkable,
    FlatGrassWalkable,
    SolidPath,
    Lava,
    WalkableMud,
    HazardousMud,
    SlowSand,
    Snow,
    SlipperyIce,
    Brick,
    Wall,
    Teleport,
};
export TileType convert_string_to_TileType(const std::string& str) {
    std::string entry = Utils::to_lower(str);

    if (str == "HighGrassWalkable") return TileType::HighGrassWalkable;
    else if (entry == "flatgrasswalkable") return TileType::FlatGrassWalkable;
    else if (entry == "solidpath") return TileType::SolidPath;
    else if (entry == "lava") return TileType::Lava;
    else if (entry == "walkablemud") return TileType::WalkableMud;
    else if (entry == "hazardousmud") return TileType::HazardousMud;
    else if (entry == "slowsand") return TileType::SlowSand;
    else if (entry == "snow") return TileType::Snow;
    else if (entry == "slipperyice") return TileType::SlipperyIce;
    else if (entry == "brick") return TileType::Brick;
    else if (entry == "wall") return TileType::Wall;
    else if (entry == "teleport") return TileType::Teleport;
    else return TileType::Unknown;
}
/**
 * There exist 7 different Types of tiles that carry different properties.
 * TileInfo class bundles all relevant types and properties
 */
export class TileInfo {
public:
    TileInfo(int l_id, int l_drag, int l_damage_per_second, TileType l_property)
        : m_id(l_id),m_drag(l_drag), m_damage_per_second(l_damage_per_second), m_type(l_property) {}
    TileInfo(const TileInfo& tile) = delete;
    TileInfo& operator=(const TileInfo& tile) = delete;
    int get_tile_id() const { return m_id; }

private:
    int m_id = -1;
    int m_drag = 0;
    int m_damage_per_second = 0;
    TileType m_type;
    std::unique_ptr<sf::Sprite> m_sprite;

};