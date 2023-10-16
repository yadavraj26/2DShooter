#pragma once
#include"SFML/Graphics.hpp"
class TileData
{
public:
	TileData(std::string& loadFilePath)
	{
		if (!texture.loadFromFile(loadFilePath))
			throw std::exception("image not found");
	}

	sf::Texture& getTexture() { return texture; }
private:
	sf::Texture texture;
};