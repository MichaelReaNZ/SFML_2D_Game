#pragma once
#include "Tile.h"
#include <fstream>
#include <iostream>

class Board {
	static const int BOARD_WIDTH = 16;
	static const int BOARD_HEIGHT = 16;

	static const int TILE_SIZE_IN_PIXELS = 64;

	Tile* m_tilePtrArray[BOARD_WIDTH][BOARD_HEIGHT];

	//tile textures
	sf::Texture* m_tileTextureArray[3];
	void PreLoadTextureAssetsFromFiles();
public:
	Board();
	~Board();
	void Update(sf::RenderWindow& _Window);

	char levelArray[BOARD_WIDTH][BOARD_HEIGHT];
	void LoadMapFromFile(std::string _FilePath);

	bool CanMoveToTile(sf::Vector2i _TilePosition);

	sf::Vector2f BoardPositionToScreenPosition(sf::Vector2i _BoardPosition);
};
