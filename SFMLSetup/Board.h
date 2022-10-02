#pragma once
#include "Tile.h"
#include <fstream>
#include <iostream>
#include "Enemy.h"

class Board {
	static const int BOARD_WIDTH = 16;
	static const int BOARD_HEIGHT = 16;

	static const int TILE_SIZE_IN_PIXELS = 64;

	Tile* m_tilePtrArray[BOARD_WIDTH][BOARD_HEIGHT];

	//std::vector<Tile*> m_levelWallTiles;


	//tile textures
	sf::Texture* m_tileTextureArray[3];
	void PreLoadTextureAssetsFromFiles();
public:
	Board();
	~Board();
	void Update(sf::RenderWindow& _Window);
	void LoadMapFromFile(std::string _FilePath);

	bool CanMoveToTile(sf::Vector2i _TilePosition);
	sf::Vector2f BoardPositionToScreenPosition(int _x, int _y);

	char levelArray[BOARD_WIDTH][BOARD_HEIGHT];
	std::vector<sf::FloatRect*> m_WorldCollisionRects;
	std::vector<Enemy*> m_Enemies;

};
