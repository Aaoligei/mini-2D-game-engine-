#pragma once
#include"tinyxml.h"
#include<map>
#include<string>
#include"GameMap.h"
#include"TileLayer.h"

class MapParser
{
public:
	bool Load();
	void Clean();

	inline GameMap* GetMap(std::string id) { return m_Maps[id]; }

	inline static MapParser* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser(); }
private:
	MapParser(){}
	static MapParser* s_Instance;
	std::map<std::string, GameMap*> m_Maps;

	bool Parse(std::string id, std::string source);
	Tileset ParseTileset(TiXmlElement* xmlTileset);
	TileLayer* ParseTileLayer(TiXmlElement* xmlTileset,TilesetList tilesets,int tilesize,int rowcount,int colcount);
};

