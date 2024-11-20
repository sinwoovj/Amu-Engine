#include "Map.h"
#include "../Data/Data.h"
#include "MapManager.h"
#include <Utils.h>
Map::Map(std::string mapName_, int width_, int height_, float spacing_) : mapName(mapName_), width(width_), height(height_), spacing(spacing_)
{
    // 맵 크기에 맞게 빈 타일로 초기화
    isViewGrid = true;
    tiles = std::vector<std::vector<Tile>>((unsigned int)height, std::vector<Tile>((unsigned int)width, Tile(Tile::TileType::Empty, false, 0, 0)));
    grid = Grid((float)width, (float)height, (float)spacing);
    MapManager::GetInstance().AddMap(this);
}

void Map::addItem(Item item) {
    items.push_back(item);
}

void Map::addSpawnPoint(int x, int y) {
    spawnPoints.push_back({ x, y });
}

void Map::setTile(int x, int y, Tile::TileType type, bool destructible) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        tiles[y][x] = Tile(type, destructible, x, y);
    }
}

void Map::Update()
{
    glm::vec2 cws = Utility::GetCurrentWindowSize();
    if (width != cws.x || height != cws.y)
    {
        grid.vertices.clear();
        grid.SetupGrid(cws.x, cws.y, spacing);
        width = cws.x;
        height = cws.y;
    }
}

void Map::GridUpdate()
{
    grid.RenderGrid();
}