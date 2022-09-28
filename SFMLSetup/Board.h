#pragma once
#include "Tile.h"
#include <fstream>
#include <iostream>

class Board {
	static const int boardWidth = 8;
	static const int boardHeight = 8;

	Tile* m_tilePtrArray[boardWidth][boardHeight];
public:
	Board(int _BoardWidth, int _BoardHeight);
	~Board();
	void Update(sf::RenderWindow& _Window);

	char levelArray[boardWidth][boardHeight];
	void LoadFile(std::string _FilePath);

	bool CanMoveToTile(sf::Vector2i _TilePosition);

	sf::Vector2f BoardPositionToScreenPosition(sf::Vector2i _BoardPosition);
};
