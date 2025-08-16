module;

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Context.hpp>
#include <string>
export module Tiles;

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

    if (str == "HighGrassWalkable") return TileType::HighGrassWalkable;
    else if (str == "FlatGrassWalkable") return TileType::FlatGrassWalkable;
    else if (str == "WalkableMud") return TileType::WalkableMud;
    else if (str == "HazardousMud") return TileType::HazardousMud;
    else if (str == "SlowSand") return TileType::SlowSand;
    else if (str == "SlipperySnow") return TileType::SlipperySnow;
    else if (str == "SlipperyIce") return TileType::SlipperyIce;
    else if (str == "SolidPath") return TileType::SolidPath;
    else if (str == "Teleport") return TileType::Teleport;
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