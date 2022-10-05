
#include "Board.h"

Board::Board()
{
	PreLoadTextureAssetsFromFiles();
	LoadMapFromFile("Assets/PixelMap.png");
	//LoadMapFromFile("Assets/Map.txt");

	//create and place enemies
	Enemy* mainEnemy = new Enemy(BoardPositionToScreenPosition(11, 4));
	m_Enemies.push_back(mainEnemy);

	//create and place door
	m_Items.push_back(new Item(BoardPositionToScreenPosition(0, 1), DOOR));
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

void Board::Update(sf::RenderWindow& _Window, sf::View _LevelView)
{
	//sf::View view = _Window.getView();

	//draw board tiles
	for (int x = 0; x < BOARD_WIDTH; x++)
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			//only if tile within current view then update (to save CPU)
			if (m_tilePtrArray[x][y]->m_TileSprite.getPosition().x > (_LevelView.getCenter().x - _LevelView.getSize().x / 2) - 64
				&& m_tilePtrArray[x][y]->m_TileSprite.getPosition().x < (_LevelView.getCenter().x + _LevelView.getSize().x / 2) + 64
				&& m_tilePtrArray[x][y]->m_TileSprite.getPosition().y >(_LevelView.getCenter().y - _LevelView.getSize().y / 2) - 64
				&& m_tilePtrArray[x][y]->m_TileSprite.getPosition().y < (_LevelView.getCenter().y + _LevelView.getSize().y / 2) + 64)
			{
				_Window.draw(m_tilePtrArray[x][y]->m_TileSprite);
			}
		}
		//m_tilePtrArray[x][y]->Update(_Window);

	}

	//draw items
	for (int i = 0; i < m_Items.size(); i++) {
		m_Items[i]->Update(_Window);
	}

	//draw enemies
	for (int i = 0; i < m_Enemies.size(); i++) {
		m_Enemies[i]->Update(_Window);
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
			sf::Color color = pixelMapImage.getPixel(x, y);
			sf::Uint8 r = color.r;
			sf::Uint8 g = color.g;
			sf::Uint8 b = color.b;

			TileType tileType = TileType_Sea;

			//brown is mountain
			if (r == 58 && g == 29 && b == 0) {
				tileType = TileType_Wall;

			}
			else if (r == 0 && g == 0 && b == 255) {
				tileType = TileType_Sea;
			}
			else if (r == 0 && g == 128 && b == 0) {
				tileType = TileType_Floor;
			}

			int yScale = y / scale;
			int xScale = x / scale;

			m_tilePtrArray[yScale][xScale] = new Tile(sf::Vector2f(xScale * 64, yScale * 64), tileType, m_tileTextureArray[tileType]);
			m_tilePtrArray[yScale][xScale]->m_TilePosition = sf::Vector2i(xScale, yScale);

			//Collision boxes
			if (tileType == TileType_Sea || tileType == TileType_Wall) {
				m_tilePtrArray[yScale][xScale]->m_AABB = new sf::FloatRect();

				m_tilePtrArray[yScale][xScale]->m_AABB->top = m_tilePtrArray[yScale][xScale]->getSprite().getGlobalBounds().top;
				m_tilePtrArray[yScale][xScale]->m_AABB->left = m_tilePtrArray[yScale][xScale]->getSprite().getGlobalBounds().left;
				m_tilePtrArray[yScale][xScale]->m_AABB->height = m_tilePtrArray[yScale][xScale]->getSprite().getGlobalBounds().height;
				m_tilePtrArray[yScale][xScale]->m_AABB->width = m_tilePtrArray[yScale][xScale]->getSprite().getGlobalBounds().width;

				//m_levelWallTiles.push_back(m_tilePtrArray[y][x]);
				m_WorldCollisionRects.push_back(m_tilePtrArray[yScale][xScale]->m_AABB);
			}
		}
	}
}




//create array of pixels
//sf::Uint8* pixels = new sf::Uint8[imageSize.x * imageSize.y * 4];




	//std::fstream loadFileStream;
	//loadFileStream.open(_FilePath, std::ios::in);

	//std::string loadFileString;
	//int lineCount = 0;

	//if (loadFileStream.is_open()) {
	//	while (std::getline(loadFileStream, loadFileString)) {
	//		for (int i = 0; i < loadFileString.size(); i++) {
	//			m_levelArray[lineCount][i] = loadFileString[i];
	//		}
	//		lineCount++;
	//	}
	//	loadFileStream.close();
	//}

	//for (int x = 0; x < BOARD_HEIGHT; x++)
	//{
	//	for (int y = 0; y < BOARD_WIDTH; y++)
	//	{
	//		if (m_levelArray[y][x] == 'x') {
	//			m_tilePtrArray[y][x] = new Tile(sf::Vector2f(x * 64, y * 64), TileType_Wall, m_tileTextureArray[TileType_Wall]);
	//			m_tilePtrArray[y][x]->m_TilePosition = sf::Vector2i(x, y);
	//		}
	//		else if (m_levelArray[y][x] == 'o') {
	//			m_tilePtrArray[y][x] = new Tile(sf::Vector2f(x * 64, y * 64), TileType_Floor, m_tileTextureArray[TileType_Floor]);
	//			m_tilePtrArray[y][x]->m_TilePosition = sf::Vector2i(x, y);
	//		}
	//		else if (m_levelArray[y][x] == 's') {
	//			m_tilePtrArray[y][x] = new Tile(sf::Vector2f(x * 64, y * 64), TileType_Sea, m_tileTextureArray[TileType_Sea]);
	//			m_tilePtrArray[y][x]->m_TilePosition = sf::Vector2i(x, y);
	//		}

	//		//Collision boxes
	//		if (m_levelArray[y][x] == 's' || m_levelArray[y][x] == 'x') {
	//			m_tilePtrArray[y][x]->m_AABB = new sf::FloatRect();

	//			m_tilePtrArray[y][x]->m_AABB->top = m_tilePtrArray[y][x]->getSprite().getGlobalBounds().top;
	//			m_tilePtrArray[y][x]->m_AABB->left = m_tilePtrArray[y][x]->getSprite().getGlobalBounds().left;
	//			m_tilePtrArray[y][x]->m_AABB->height = m_tilePtrArray[y][x]->getSprite().getGlobalBounds().height;
	//			m_tilePtrArray[y][x]->m_AABB->width = m_tilePtrArray[y][x]->getSprite().getGlobalBounds().width;

	//			//m_levelWallTiles.push_back(m_tilePtrArray[y][x]);
	//			m_WorldCollisionRects.push_back(m_tilePtrArray[y][x]->m_AABB);
	//		}
	//	}
	//}
//}

//Will span underneath enemy when it is killed
void Board::SpawnKey() {
	sf::Vector2f lastEnemyLocation = m_Enemies.front()->m_Shape.getPosition();
	m_Items.push_back(new Item(lastEnemyLocation, KEY));
}
