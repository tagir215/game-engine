#include "engine/components/textcomponent.h"

TextComponent::TextComponent(std::string& fontDataPath, std::string& fontImagePath)
{
	std::vector<FontCharacterInfo> charInfos = fontSerializer.deserializeFontInfo(fontDataPath);
	for (int i = 0; i < charInfos.size(); ++i) {
		wchar_t wchar = static_cast<wchar_t>(charInfos[i].id);
		charInfoMap[wchar] = charInfos[i];
	}

	TextureManager textureManager;
	textureComponent = textureManager.loadTextureFromPath(fontImagePath);
}

void TextComponent::calculateCharPlaneVertices(
	std::vector<float>& vertices, std::vector<float>& texCoords, int x, int y, FontCharacterInfo& ci) 
{
	float cx = x + ci.xoffset;
	float cy = y - ci.yoffset;
	float w = ci.width;
	float h = ci.height;
	float plane[] = {
		cx,   cy,   0,
		cx+w, cy,   0,
		cx+w, cy-h, 0,
		cx,   cy,   0,
		cx+w, cy-h, 0,
		cx,   cy-h, 0
	};

	textWidth += ci.xadvance;

	for (float v : plane) {
		vertices.push_back(v);
	}

	float tx = ci.x / ATLAS_WIDTH;
	float ty = 1 - ci.y / ATLAS_WIDTH;
	float tw = ci.width / ATLAS_WIDTH;
	float th = ci.height / ATLAS_WIDTH;

	float cTextCoords[] = {
		tx,     ty,
		tx+tw,  ty,
		tx+tw,  ty - th,
		tx,     ty,
		tx+tw,  ty - th,
		tx,     ty - th
	};

	for (float tc : cTextCoords) {
		texCoords.push_back(tc);
	}
}

void centerText(std::vector<float>& vertices, float textWidth, float textHeight) 
{
	float translateX = textWidth / 2;
	float translateY = textHeight / 2;
	int dumbPersonWayToDoThis = 0;
	for (int i = 0; i < vertices.size(); ++i) {
		if (dumbPersonWayToDoThis == 0) {
			vertices[i] -= translateX;
		}
		else if (dumbPersonWayToDoThis == 1) {
			vertices[i] -= translateY;
		}
		if (++dumbPersonWayToDoThis > 2) dumbPersonWayToDoThis = 0;
	}
}

void TextComponent::generateMesh()
{
	if (charInfoMap.size() == 0) {
		std::cerr << "no charInfo" << std::endl;
		return;
	}
	std::vector<float>vertices;
	std::vector<float>texCoords;
	int currentX = 0;
	int currentY = 0;
	textWidth = 0;
	textHeight = 0;

	for (int i = 0; i < text.length(); ++i) {
		FontCharacterInfo ci = charInfoMap[text[i]];
		calculateCharPlaneVertices(vertices, texCoords, currentX, currentY, ci);
		currentX += ci.xadvance;
		if (ci.height > textHeight) {
			textHeight = ci.height;
		}
	}

	centerText(vertices, textWidth, textHeight);

	mesh = new StaticMesh(vertices, texCoords);
	mesh->initVertexArrays();
}
