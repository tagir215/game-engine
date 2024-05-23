#include "engine/components/tilemap.h"
#include "engine/graphics/texturemanager.h"
#include <tinyxml2.h>
#include <iostream>
#include <sstream>
#include <regex>

std::vector<long long> stringToVector(const std::string& str) {
	std::vector<long long> result;
	std::stringstream ss(str);
	std::string token;

	while (getline(ss, token, ',')) {
		std::string sOutput = std::regex_replace(token, std::regex(R"([\D])"), "");
		long long num = std::stoll(sOutput);
		result.push_back(num);
	}

	return result;
}

TileMap::TileMap(Scene* scene, const std::string& pathToImage, const std::string& pathToTmx, const std::string& pathToTsx) : GameObject(scene)
{
	TextureManager textureManager;
	TextureComponent* texture = textureManager.loadTextureFromPath(pathToImage);
	setTextureComponent(texture);
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError resultTmx =  doc.LoadFile(pathToTmx.c_str());

	if (resultTmx != tinyxml2::XML_SUCCESS) {
		std::cerr << "Error loading XML file: " << doc.ErrorName() << std::endl;
	}

	tinyxml2::XMLElement* root = doc.RootElement();
	tinyxml2::XMLElement* layer = root->FirstChildElement("layer");
	tinyxml2::XMLElement* data = layer->FirstChildElement("data");
	const std::string text(data->GetText());
	tiles = stringToVector(text);

	tinyxml2::XMLError resultTsx = doc.LoadFile(pathToTsx.c_str());
	if (resultTsx != tinyxml2::XML_SUCCESS) {
		std::cerr << "Error loading XML file: " << doc.ErrorName() << std::endl;
	}

	tinyxml2::XMLElement* rootTsx = doc.RootElement();
	tileWidth = std::stoi(rootTsx->FindAttribute("tilewidth")->Value());
	tileHeight = std::stoi(rootTsx->FindAttribute("tileheight")->Value());
	tileCount = std::stoi(rootTsx->FindAttribute("tilecount")->Value());
	columns = std::stoi(rootTsx->FindAttribute("columns")->Value());

	createMesh();
	createComponent<StaticMesh>(vertices, texCoords);
	getMeshComponent()->initVertexArrays();

	createComponent<ShaderComponent>(0);
}

void getCoordinatesFromID(int id, int columns, float& x, float& y) {
	x = id % columns;
	y = id / columns;
	x /= columns;
	y /= columns;
}

void TileMap::createMesh()
{
	float y = 0;
	float x = 0;
	float offsetX = 30 * tileWidth;
	float offsetY = 30 * tileHeight;
	for (int i = 0; i < tiles.size(); ++i) {
		if (tiles[i] > 0) {
			std::vector<float>sq = {
				x*tileWidth - offsetX,             y*tileHeight + offsetY + tileHeight,  0,
				x*tileWidth - offsetX + tileWidth, y*tileHeight + offsetY + tileHeight,  0,
				x*tileWidth - offsetX + tileWidth, y*tileHeight + offsetY,               0,
				x*tileWidth - offsetX,             y*tileHeight + offsetY + tileHeight,  0,
				x*tileWidth - offsetX + tileWidth, y*tileHeight + offsetY,               0,
				x*tileWidth - offsetX,             y*tileHeight + offsetY,               0
			};
			for (float f : sq) {
				vertices.push_back(f);
			}
			float id = tiles[i];
			if (id > 1000) {
				id = 105;
			}
			float tx, ty;
			float tw = 1 / columns;
			getCoordinatesFromID(id, columns, tx, ty);
			std::vector<float>tcoords = {
				tx,    ty,
				tx + tw, ty,
				tx + tw, ty - tw,
				tx,    ty,
				tx + tw, ty - tw,
				tx,    ty - tw
			};
			for (float f : tcoords) {
				texCoords.push_back(f);
			}
		}
		if (++x >= 60) {
			--y;
			x = 0;
		}
	}
}

