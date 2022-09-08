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

	TileType CheckTile(sf::Vector2i _Position) { return m_tilePtrArray[_Position.y][_Position.x]->m_TileType; }
};
