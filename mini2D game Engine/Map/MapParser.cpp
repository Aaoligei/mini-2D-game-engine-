#include "MapParser.h"

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load()
{
	return Parse("Map", "assets/map/level1.tmx");
}

void MapParser::Clean()
{
	std::map<std::string, GameMap*>::iterator it;
	for (it = m_Maps.begin(); it != m_Maps.end(); it++) {
		it->second = nullptr;
	}
	m_Maps.clear();
}

/*-------------------------------˽�з���---------------------------------*/

bool MapParser::Parse(std::string id, std::string source)
{
	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error()) {
		std::cerr << "Failed to load: " << source << std::endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();
	int rowcount, colcount, tilesize = 0;

	root->Attribute("width", &colcount);
	root->Attribute("height", &rowcount);
	root->Attribute("tilewidth", &tilesize);

	//����xml��ȡ����tileset
	TilesetList tilesets;
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("tileset")) {
			tilesets.push_back(ParseTileset(e));
		}
	}

	GameMap* gamemap = new GameMap();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("layer")) {
			TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
			gamemap->m_MapLayers.push_back(tilelayer);
		}
	}

	m_Maps[id] = gamemap;
	return true;
	
}

//��xml�ж�ȡ����ʼ��һ��tileset
Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset)
{
	Tileset tileset;
	tileset.Name = xmlTileset->Attribute("name");
	xmlTileset->Attribute("firstgid",&tileset.FirstID);

	xmlTileset->Attribute("tilecount", &tileset.TileCount);
	tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

	xmlTileset->Attribute("columns", &tileset.ColCount);
	tileset.RowCount = tileset.TileCount / tileset.ColCount;
	xmlTileset->Attribute("tilewidth", &tileset.TileSize);

	//TiXmlElement* image = xmlTileset->FirstChildElement();
	//tileset.Source = image->Attribute("source");

	if (xmlTileset->FirstChildElement()->Value() == std::string("image")) {
		tileset.Source = xmlTileset->FirstChildElement("image")->Attribute("source");
	}
	else {
		tileset.Source = xmlTileset->Attribute("source");
	}

	return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount)
{
	TiXmlElement* data = nullptr;
	for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("data")) {
			//�õ�data��ͣ��
			data = e;
			break;
		}
	}
	if (data == nullptr) {
		// ������󣺿����׳��쳣������ nullptr ���¼������־
		throw std::runtime_error("Missing <data> element in XML layer");
		// ���� return nullptr;
	}
	std::string matrix(data->GetText());
	std::istringstream iss(matrix);
	std::string id;
	
	//��ʼ����ͼ
	TileMap tilemap(rowcount, std::vector<int>(colcount,0));

	for (int row = 0; row < rowcount; row++) {
		for (int col = 0; col < colcount; col++) {
			std::getline(iss, id, ',');
			std::stringstream convertor(id);
			convertor >> tilemap[row][col];

			if (!iss.good()) {
				break;
			}
		}
	}

	return new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets);
}
