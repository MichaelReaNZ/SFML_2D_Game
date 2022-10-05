#pragma once
#include "Board.h"
#include "Collisions.h"

Board::Board()
{
	PreLoadTextureAssetsFromFiles();
	LoadMapFromFile("Assets/PixelMap.png");

	//Define Levels
	//level 1 is in bottom right corner
	level1View = sf::View(sf::FloatRect(1024 - 32, 1024 - (64 * 2) - 32, 1024, 1024 + (64 * 2)));
	//level 2 is in bottom left corner
	level2View = sf::View(sf::FloatRect(0 - 32, 1024 - (64 * 2) - 32, 1024, 1024 + (64 * 2)));
	//level 3 is in top left corner
	level3View = sf::View(sf::FloatRect(0 - 32, 0 - 32 - (64 * 2), 1024, 1024 + (64 * 2)));
	//level 4 is in top right corner
	level4View = sf::View(sf::FloatRect(1024 - 32, 0 - 32 - (64 * 2), 1024, 1024 + (64 * 2)));

	m_CurrentLevelView = &level1View;

	//load high score from .txt file
	std::ifstream highScoreFile;
	highScoreFile.open("Assets/HighScore.txt");
	highScoreFile >> m_HighScore;
	highScoreFile.close();
}

Board::~Board()
{
	for (int i = 0; i < m_Enemies.size(); i++) {
		delete m_Enemies[i];
	}

	for (int i = 0; i < m_WorldCollisionRects.size(); i++) {
		delete m_WorldCollisionRects[i];
	}

	for (int i = 0; i < 3; i++) {
		delete m_tileTextureArray[i];
	}

	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			delete m_tilePtrArray[i][j];
		}
	}

	for (int i = 0; i < m_Items.size(); i++) {
		delete m_Items[i];
	}
}

void Board::PreLoadTextureAssetsFromFiles() {

	m_tileTextureArray[TileType_Wall] = new sf::Texture();
	m_tileTextureArray[TileType_Wall]->loadFromFile("Assets/Obstacle.png");

	m_tileTextureArray[TileType_Floor] = new sf::Texture();
	m_tileTextureArray[TileType_Floor]->loadFromFile("Assets/Floor.png");

	m_tileTextureArray[TileType_Sea] = new sf::Texture();
	m_tileTextureArray[TileType_Sea]->loadFromFile("Assets/Sea.png");
}

void Board::Update(sf::RenderWindow& _Window, sf::View* _LevelView)
{
	sf::Vector2f viewCentre(_LevelView->getCenter());
	sf::Vector2f viewSize(_LevelView->getSize());

	//draw board tiles
	for (int x = 0; x < BOARD_WIDTH; x++)
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			if (IsPositionInsideView(_LevelView, m_tilePtrArray[x][y]->m_TileSprite.getPosition())) {
				m_tilePtrArray[x][y]->Update(_Window);
			}
		}
	}

	//draw items
	for (int i = 0; i < m_Items.size(); i++) {
		if (IsPositionInsideView(_LevelView, m_Items[i]->m_Shape.getPosition())) {
			m_Items[i]->Update(_Window);
		}
	}

	//draw enemies
	for (int i = 0; i < m_Enemies.size(); i++) {
		if (IsPositionInsideView(_LevelView, m_Enemies[i]->m_Shape.getPosition())) {
			m_Enemies[i]->Update(_Window);
		}
	}
}

//convert board position to screen position
sf::Vector2f Board::BoardPositionToScreenPosition(int _x, int _y)
{
	sf::Vector2f screenPosition;
	screenPosition.x = _x * 64;
	screenPosition.y = _y * 64;
	return screenPosition;
}

bool Board::CanMoveToTile(sf::Vector2i _TilePosition)
{
	//check if y index is witin bounds of the array
	if (_TilePosition.y < 0 || _TilePosition.y >= BOARD_HEIGHT)
	{
		return false;
	}

	//check if x index is witin bounds of the array
	if (_TilePosition.x < 0 || _TilePosition.x >= BOARD_WIDTH)
	{
		return false;
	}

	//check if tile at that position exists
	if (m_tilePtrArray[_TilePosition.y][_TilePosition.x]->m_TileType != NULL) {
		//check if tile is a wall
		if (m_tilePtrArray[_TilePosition.y][_TilePosition.x]->m_TileType == TileType_Wall) {
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}

void Board::LoadMapFromFile(std::string _FilePath) {
	int scale = 4;

	//load image
	sf::Image pixelMapImage = sf::Image();
	pixelMapImage.loadFromFile(_FilePath);

	//get image size
	sf::Vector2u imageSize = pixelMapImage.getSize();

	//for each pixel in image add tile to m_tilePtrArray
	for (int x = 0; x < imageSize.x; x += scale)
	{
		for (int y = 0; y < imageSize.y; y += scale)
		{
			int yScale = y / scale;
			int xScale = x / scale;

			sf::Color color = pixelMapImage.getPixel(x, y);
			sf::Uint8 r = color.r;
			sf::Uint8 g = color.g;
			sf::Uint8 b = color.b;

			TileType tileType = TileType_Sea;

			if (r == 58 && g == 29 && b == 0) {
				tileType = TileType_Wall;

			}
			else if (r == 0 && g == 0 && b == 255) {
				tileType = TileType_Sea;
			}
			else if (r == 0 && g == 128 && b == 0) {
				tileType = TileType_Floor;
			}
			else if (r == 255 && g == 0 && b == 0) {
				//Enemy
				tileType = TileType_Floor;
				Enemy* enemy = new Enemy(sf::Vector2f(xScale * 64, yScale * 64));
				m_Enemies.push_back(enemy);
			}
			else if (r == 255 && g == 255 && b == 255) {
				//Door
				tileType = TileType_Floor;
				m_Items.push_back(new Item(sf::Vector2f(xScale * 64, yScale * 64), DOOR));
			}

			m_tilePtrArray[yScale][xScale] = new Tile(sf::Vector2f(xScale * 64, yScale * 64), tileType, m_tileTextureArray[tileType]);
			m_tilePtrArray[yScale][xScale]->m_TilePosition = sf::Vector2i(xScale, yScale);

			//Collision boxes
			if (tileType == TileType_Sea || tileType == TileType_Wall) {
				m_tilePtrArray[yScale][xScale]->m_AABB = new sf::FloatRect();
				m_tilePtrArray[yScale][xScale]->m_AABB->top = m_tilePtrArray[yScale][xScale]->getSprite().getGlobalBounds().top;
				m_tilePtrArray[yScale][xScale]->m_AABB->left = m_tilePtrArray[yScale][xScale]->getSprite().getGlobalBounds().left;
				m_tilePtrArray[yScale][xScale]->m_AABB->height = m_tilePtrArray[yScale][xScale]->getSprite().getGlobalBounds().height;
				m_tilePtrArray[yScale][xScale]->m_AABB->width = m_tilePtrArray[yScale][xScale]->getSprite().getGlobalBounds().width;

				m_WorldCollisionRects.push_back(m_tilePtrArray[yScale][xScale]->m_AABB);
			}
		}
	}
}

void Board::TransitionLevel(sf::Vector2f _CharacterPosition) {
	//change to level if player is inside of that view
	if (IsPositionInsideView(&level1View, _CharacterPosition)) {
		m_CurrentLevelView = &level1View;
	}
	else if (IsPositionInsideView(&level3View, _CharacterPosition)) {
		m_CurrentLevelView = &level3View;
	}
	else if (IsPositionInsideView(&level2View, _CharacterPosition)) {
		m_CurrentLevelView = &level2View;
	}

	else if (IsPositionInsideView(&level4View, _CharacterPosition)) {
		m_CurrentLevelView = &level4View;
	}
}

void Board::IncrementScore()
{
	m_Score += rand() % 20 + 5;
	//if score is larger than highscore then save
	if (m_Score > m_HighScore) {
		m_HighScore = m_Score;
		//save to "Assets/HighScore.txt"
		std::ofstream file;
		file.open("Assets/HighScore.txt");
		file << m_HighScore;
		file.close();
	}

}

int Board::GetEnemiesRemainingInLevel()
{
	int _EnemiesRemainingInLevel = 0;
	//for each enemy if it's inside the view increment m_EnemiesRemainingInLevel
	for (int i = 0; i < m_Enemies.size(); i++) {
		if (IsPositionInsideView(m_CurrentLevelView, m_Enemies[i]->m_Shape.getPosition())) {
			_EnemiesRemainingInLevel++;
		}
	}

	return _EnemiesRemainingInLevel;
}