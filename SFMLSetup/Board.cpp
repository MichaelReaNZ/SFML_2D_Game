
#include "Board.h"

Board::Board(int _BoardWidth, int _BoardHeight)
{
	LoadFile("Assets/Map.txt");
}

Board::~Board()
{

}

void Board::Update(sf::RenderWindow& _Window)
{
	for (int x = 0; x < boardWidth; x++)
	{
		for (int y = 0; y < boardHeight; y++)
		{
			m_tilePtrArray[x][y]->Update(_Window);
		}
	}
}

//convert board position to screen position
sf::Vector2f Board::BoardPositionToScreenPosition(sf::Vector2i _BoardPosition)
{
	sf::Vector2f screenPosition;
	screenPosition.x = _BoardPosition.x * 64;
	screenPosition.y = _BoardPosition.y * 64;
	return screenPosition;
}

bool Board::CanMoveToTile(sf::Vector2i _TilePosition)
{
	//get m_tilePtrArray height
	int height = sizeof(m_tilePtrArray) / sizeof(m_tilePtrArray[0]);
	//get m_tilePtrArray width
	int width = sizeof(m_tilePtrArray[0]) / sizeof(m_tilePtrArray[0][0]);

	//check if y index is witin bounds of the array
	if (_TilePosition.y < 0 || _TilePosition.y >= height)
	{
		return false;
	}

	//check if x index is witin bounds of the array
	if (_TilePosition.x < 0 || _TilePosition.x >= width)
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

void Board::LoadFile(std::string _FilePath) {
	std::fstream loadFileStream;
	loadFileStream.open(_FilePath, std::ios::in);

	std::string loadFileString;
	int lineCount = 0;

	if (loadFileStream.is_open()) {
		while (std::getline(loadFileStream, loadFileString)) {
			for (int i = 0; i < loadFileString.size(); i++) {
				levelArray[lineCount][i] = loadFileString[i];
			}
			lineCount++;
		}
		loadFileStream.close();
	}

	for (int x = 0; x < boardHeight; x++)
	{
		for (int y = 0; y < boardWidth; y++)
		{
			if (levelArray[y][x] == 'x') {
				m_tilePtrArray[y][x] = new Tile(sf::Vector2f(x * 64, y * 64), TileType_Wall);
				m_tilePtrArray[y][x]->m_TilePosition = sf::Vector2i(x, y);
			}
			else if (levelArray[y][x] == 'o') {
				m_tilePtrArray[y][x] = new Tile(sf::Vector2f(x * 64, y * 64), TileType_Floor);
				m_tilePtrArray[y][x]->m_TilePosition = sf::Vector2i(x, y);
			}

		}
	}
}
