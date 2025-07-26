module;
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Context.hpp>


export module Tiles;

export enum class TileProperty {
    Walkable,
    Hazard,
    Slow,
    Slippery,
    Solid,
    Teleport,
};

export class TileInfo {
public:
    TileInfo(int l_id, int l_drag, int l_hazard, TileProperty l_property)
        : m_id(l_id),m_drag(l_drag), m_hazard(l_hazard), m_property(l_property) {}
    TileInfo(const TileInfo& tile) = delete;
    TileInfo& operator=(const TileInfo& tile) = delete;
    int get_tile_id() const { return m_id; }

private:
    int m_id = -1;
    int m_drag = 0;
    int m_hazard = 0;
    TileProperty m_property;
    std::unique_ptr<sf::Sprite> m_sprite;

};