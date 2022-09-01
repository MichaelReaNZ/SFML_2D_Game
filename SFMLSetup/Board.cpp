
#include "Board.h"

Board::Board(int _BoardWidth, int _BoardHeight)
{
	for (int x = 0; x < _BoardWidth; x++)
	{
		for (int y = 0; y < _BoardHeight; y++)
		{
			m_tilePtrArray[x][y] = new Tile(sf::Vector2f(x * 64, y * 64));
			m_tilePtrArray[x][y]->m_TilePosition = sf::Vector2i(x, y);
		}
	}
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