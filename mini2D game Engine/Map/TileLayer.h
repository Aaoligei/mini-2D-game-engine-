#pragma once
#include "Layer.h"
#include<string>
#include<vector>

struct Tileset {
    int FirstID, LastID;
    int RowCount,ColCount;
    int TileCount, TileSize;
    std::string Name, Source;
};

using TilesetList = std::vector<Tileset>;
//二维数组存放tilemap
using TileMap = std::vector<std::vector<int>>;

class TileLayer :
    public Layer
{
public:
    TileLayer(int tilesize,int rowcount,int colcount,TileMap tilemap,TilesetList tilesetlist);
    virtual void Render() override;
    virtual void Update() override;
    inline TileMap GetTileMap() { return m_TileMap; }

private:
    int m_TileSize;
    int m_RowCount, m_ColCount;
    TileMap m_TileMap;
    TilesetList m_TilesetList;
};

