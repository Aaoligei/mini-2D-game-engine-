#include "TileLayer.h"
#include"../Graphics/TextureManager.h"
#include <iostream>

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesetlist):
    m_TileMap(tilemap),m_TilesetList(tilesetlist)
{

    m_ColCount = colcount;
    m_RowCount = rowcount;
    m_TileSize = tilesize;

    for (unsigned int i = 0; i < m_TilesetList.size(); i++) {
        TextureManager::GetInstance()->Load(m_TilesetList[i].Name, "assets/map/" + m_TilesetList[i].Source);
    }
}

void TileLayer::Render()
{
    for (unsigned int i = 0; i < m_RowCount; i++) {
        for (unsigned int j = 0; j < m_ColCount; j++) {
            int tileID = m_TileMap[i][j];

            
            if (tileID == 0) continue;
            else {
                int index = 0;
                if (m_TilesetList.size() > 1) {
                    for (unsigned int k = 0; k < m_TilesetList.size(); k++) {
                        if (tileID > m_TilesetList[k].FirstID && tileID < m_TilesetList[k].LastID) {
                            tileID = tileID + m_TilesetList[k].TileCount - m_TilesetList[k].LastID;
                            index = k;
                            break;
                        }
                    }
                }
                Tileset ts = m_TilesetList[index];
                int tileRow = tileID / ts.ColCount;
                int tileCol = tileID - tileRow * ts.ColCount - 1;

                if (tileID % ts.ColCount == 0) {
                    tileRow--;
                    tileCol = ts.ColCount - 1;
                }

                TextureManager::GetInstance()->DrawTile(ts.Name, ts.TileSize, j * ts.TileSize, i * ts.TileSize, tileRow, tileCol);
            }

            
        }
    }
}

void TileLayer::Update()
{
}
