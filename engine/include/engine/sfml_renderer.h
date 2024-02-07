#pragma once
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <memory>

namespace engine {

///
/// \brief The SFMLRenderer class
///
class SFMLRenderer {
public:
	SFMLRenderer(int sizeX, int sizeY, const std::string& title) {
		m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(sizeX,sizeY), title.c_str());
	}

	bool isWindowOpen() const {
		return m_window && m_window->isOpen();
	}

	void onBeginFrame() {
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				m_window->close();
		}

		// clear the window with some color
		m_window->clear(sf::Color(64, 64, 32));
	}

	void onEndFrame() {
		// End the current frame
		m_window->display();
	}

	void drawTile(glm::vec2 position, const glm::vec2& tileSize, size_t tileID) {
		assert(tileID >= 0 && tileID < m_textures.size());
		const auto& texture = *m_textures[tileID];
		position.x *= tileSize.x;
		position.y *= tileSize.y;
		auto texSize = texture.getSize();
		sf::Sprite sprite;
		sprite.setOrigin(texSize.x * 0.5f, texSize.y * 0.5f);
		sprite.setTexture(texture);
		sprite.setPosition(sf::Vector2f(position.x,position.y) + 0.5f * sf::Vector2f(tileSize.x, tileSize.y));
		auto scale = sf::Vector2f(tileSize.x / texSize.x, tileSize.y / texSize.y);
		sprite.setScale(scale);
		m_window->draw(sprite);
	}

	void drawSprite(glm::vec2 position, float rotation, const glm::vec2& size, const glm::vec2& tileSize, size_t textureId) {
		assert(textureId >= 0 && textureId < m_textures.size());
		position.x *= tileSize.x;
		position.y *= tileSize.y;
		const auto& texture = *m_textures[textureId];
		auto texSize = texture.getSize();
		const auto OFFSET = sf::Vector2f(size.x * 0.5f * tileSize.x, size.y * 0.5f * tileSize.y);
		sf::Sprite sprite;
		sprite.setTexture(texture);
		sprite.setOrigin(texSize.x * 0.5f, texSize.y * 0.5f);
		sprite.setRotation(rotation * 180.0f / 3.1415f);
		sprite.setPosition(sf::Vector2f(position[0], position[1]) + 0.5f * sf::Vector2f(tileSize[0], tileSize[1]));
		auto scale = sf::Vector2f(size.x * tileSize.x / texSize.x, size.y * tileSize.y / texSize.y);
		sprite.setScale(scale);
		m_window->draw(sprite);
	}

	void drawText(glm::vec2 position, const std::string& str, int fontId, int charSize, const glm::vec4& color) {
		assert(fontId >= 0 && fontId < m_fonts.size());
		auto font = m_fonts[fontId].get();
		sf::Text text;
		auto windoSize = m_window->getSize();
		text.setPosition(sf::Vector2f(windoSize.x*position[0], windoSize.y*position[1]));
		text.setFont(*font);
		text.setString(str);
		text.setCharacterSize(charSize);
		text.setFillColor(sf::Color(255.0f*color[0], 255.0f*color[1], 255.0f*color[2], 255.0f*color[3]));
		m_window->draw(text);
	}



	//void renderSprite();
	//void renderText();
	//void renderTiles();

private:
	SFMLRenderer();
	SFMLRenderer(const SFMLRenderer&);
	SFMLRenderer& operator=(const SFMLRenderer&);

	std::shared_ptr<sf::RenderWindow> m_window;
	std::vector<std::shared_ptr<sf::Font> > m_fonts;
	std::vector<std::shared_ptr<sf::Texture> > m_textures;
};


} // End - namespace engine

