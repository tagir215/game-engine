#pragma once

#include <string>
#include <vector>
#include "engine/core/gameobject.h"

class TileMap : public GameObject {
public:
	TileMap(Scene* scene, const std::string& pathToImage, const std::string& pathToTmx, const std::string& pathToTsx);
	const std::vector<long long>& getTiles() const {
		return tiles;
	}
private:
	std::vector<long long>tiles;
	int tileWidth = 0;
	int tileHeight = 0;
	int tileCount = 0;
	int columns = 0;
	std::vector<float>vertices;
	std::vector<float>texCoords;

	void createMesh();
};
