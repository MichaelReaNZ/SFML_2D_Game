#pragma once
#include "SFML/Graphics.hpp"

enum TileType
{
	TileType_Wall,
	TileType_Floor,
	TileType_Sea
};

class Tile
{
	//64 x 64 tiles
	//ref for the character currently on the tile

private:
	//sf::RectangleShape m_TileShape; // the 2d image of the tile
	sf::Texture* m_Texture; // the texture of the tile



public:
	sf::Sprite m_TileSprite; //TODO: Should I use a pointer?
	sf::Vector2i m_TilePosition;
	sf::FloatRect* m_AABB; //the bounding volume

	TileType m_TileType;

	Tile(sf::Vector2f _Position, TileType _Type, sf::Texture* _Texture);
	~Tile();

	sf::Sprite getSprite() { return m_TileSprite; }

	void Update(sf::RenderWindow& _Window);

};

