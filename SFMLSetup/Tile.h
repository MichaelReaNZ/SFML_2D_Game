#pragma once
#include "SFML/Graphics.hpp"

class Tile
{
	//rect shape or a sprite
	//position (vector, int value)

	//64 x 64 tiles
	//ref for the character currently on the tile

private:

	sf::RectangleShape m_TileShape; // the 2d image of the tile
	sf::Texture* m_texture; // the texture of the tile

public:
	sf::Vector2i m_TilePosition;

	Tile(sf::Vector2f _Position);
	~Tile();

	void Update(sf::RenderWindow& _Window);

};

