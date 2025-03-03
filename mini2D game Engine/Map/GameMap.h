#pragma once
#include"Layer.h"
#include<vector>

class GameMap
{
public:
	void Render() {
		for (auto layer : m_MapLayers) {
			layer->Render();
		}
	}

	void Update() {
		for (auto layer : m_MapLayers) {
			layer->Update();
		}
	}

	std::vector<Layer*> GetMapLayers() { return m_MapLayers; }

private:
	std::vector<Layer*> m_MapLayers;
};

