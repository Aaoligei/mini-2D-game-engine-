#include "TileLayer.h"

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesetlist)
{
	m_TileMap = tilemap;
	m_TilesetList = tilesetlist;
	m_ColCount = colcount;
	m_RowCount = rowcount;
	m_TileSize = tilesize;
}

void TileLayer::Render()
{
}

void TileLayer::Update()
{
}
