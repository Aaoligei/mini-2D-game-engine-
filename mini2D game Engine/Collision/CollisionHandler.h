#pragma once
#include"SDL.h"
#include<vector>
#include"../Map/TileLayer.h"
#include"../Map/GameMap.h"
#include"../core/Engine.h"

class CollisionHandler
{
public:
	bool CheckCollision(SDL_Rect a, SDL_Rect b);
	bool MapCollision(SDL_Rect a);

	inline static CollisionHandler* GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new CollisionHandler();
		}
		return s_Instance;
	};

private:
	CollisionHandler();
	static CollisionHandler* s_Instance;

	TileMap m_CollisonTilemap;
	TileLayer* m_CollisionLayer;
};
