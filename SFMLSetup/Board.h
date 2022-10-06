#pragma once
#include "Tile.h"
#include <fstream>
#include <iostream>
#include "Enemy.h"
#include "Item.h"
#include "Collisions.h"
#include "Enums.h"
#include <SFML/Audio.hpp>

class Board {
	static const int BOARD_WIDTH = 16 * 2;
	static const int BOARD_HEIGHT = 16 * 2;
	static const int TILE_SIZE_IN_PIXELS = 64;

	//level 1 is in bottom right corner
	sf::View level1View;
	//level 2 is in bottom left corner
	sf::View level2View;
	//level 3 is in top left corner
	sf::View level3View;
	//level 4 is in top right corner
	sf::View level4View;

	//tile textures
	sf::Texture* m_tileTextureArray[3];
	void PreLoadTextureAssetsFromFiles();

	sf::Music m_music;
public:
	Board();
	~Board();
	void Update(sf::RenderWindow& _Window, sf::View* _LevelView);
	void LoadMapFromFile(std::string _FilePath);

	bool CanMoveToTile(sf::Vector2i _TilePosition);
	sf::Vector2f BoardPositionToScreenPosition(int _x, int _y);

	Tile* m_tilePtrArray[BOARD_WIDTH][BOARD_HEIGHT];
	char m_levelArray[BOARD_WIDTH][BOARD_HEIGHT];

	std::vector<sf::FloatRect*> m_WorldCollisionRects;

	std::vector<Enemy*> m_Enemies;
	std::vector<Item*> m_Items;
	std::vector<Bullet*> m_Bullets;

	float m_EnemyMoveSpeed = 6.0f;
	float m_EnemyShootSpeed = 6.0f;

	sf::View* m_CurrentLevelView;
	bool m_IsGameComplete = false;
	sf::Clock m_TimeSinceGameStart;
	int m_Score;
	int m_HighScore;


	void TransitionLevel(sf::Vector2f _CharacterPosition);
	int GetEnemiesRemainingInLevel();
	void IncrementScore();

	void EnemyMovement();
	void EnemyAttack(sf::Vector2f _CharacterPosition);
};
