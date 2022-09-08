
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