#pragma once
#include "Tile.h"

class Board {
	static const int boardWidth = 8;
	static const int boardHeight = 8;

	Tile* m_tilePtrArray[boardWidth][boardHeight];
public:
	Board(int _BoardWidth, int _BoardHeight);
	~Board();
	void Update(sf::RenderWindow& _Window);
};
