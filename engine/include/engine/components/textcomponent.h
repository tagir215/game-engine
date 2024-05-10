#pragma once
#include <string>
#include "engine/graphics/fontcharacterinfo.h"
#include <glm/glm.hpp>
#include <map>
#include "engine/components/mesh.h"
#include "engine/graphics/texture.h"
#include "engine/util/fontserializer.h"
#include "engine/graphics/texturemanager.h"

class TextComponent {
public:
	TextComponent(std::string fontDataPath, std::string fontImagePath);
	~TextComponent() {
		delete mesh;
		delete textureComponent;
	}

	void setText(std::string text) {
		this->text = text;
		delete mesh;
		generateMesh();
	}
	void setColor(glm::vec3 color) {
		this->color = color;
	}
	void generateMesh();

	StaticMesh* getStaticTextMesh() const {
		return mesh;
	}
	TextureComponent* getTextureComponent() const {
		return textureComponent;
	}

private:
	StaticMesh* mesh = nullptr;
	TextureComponent* textureComponent = nullptr;
	std::string text;
	glm::vec3 color;
	std::map<wchar_t, FontCharacterInfo>charInfoMap;
	void calculateCharPlaneVertices(
		std::vector<float>& vertices, std::vector<float>& texCoords, int x, int y, FontCharacterInfo& ci);
	const float ATLAS_WIDTH = 512;
	FontSerializer fontSerializer;
	std::vector<FontCharacterInfo> chars;
	float textWidth = 0;
	float textHeight = 0;
};
