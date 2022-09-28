#include "Tile.h"

Tile::Tile(sf::Vector2f _Position, TileType _Type, sf::Texture* _Texture)
{
	m_TileShape.setSize(sf::Vector2f(64, 64));
	m_TileShape.setPosition(_Position);
	m_TileShape.setTexture(_Texture);

	m_TileType = _Type;

	//set outline color to grey and make it thin
	m_TileShape.setOutlineColor(sf::Color::Blue);
	m_TileShape.setOutlineThickness(5);
}

Tile::~Tile()
{
	//delete m_texture;
}

void Tile::Update(sf::RenderWindow& _Window)
{
	_Window.draw(m_TileShape);
}