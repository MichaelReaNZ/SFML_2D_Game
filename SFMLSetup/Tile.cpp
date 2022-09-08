#include "Tile.h"

Tile::Tile(sf::Vector2f _Position, TileType _Type) //TODO pass in the texture to not load it everytime
{
	m_TileShape.setSize(sf::Vector2f(64, 64));
	m_TileShape.setPosition(_Position);

	m_texture = new sf::Texture();

	switch (_Type)
	{
	case TileType_Floor:
		m_texture->loadFromFile("Assets/Floor.png");
		break;
	case TileType_Wall:
		m_texture->loadFromFile("Assets/Obstacle.png");
		break;
	}

	//m_texture->loadFromFile("Assets/Tile.png");

	m_TileShape.setTexture(m_texture);

	m_TileType = _Type;

	//set outline color to grey and make it thin
	m_TileShape.setOutlineColor(sf::Color::Blue);
	m_TileShape.setOutlineThickness(5);
}

Tile::~Tile()
{
	delete m_texture;
}

void Tile::Update(sf::RenderWindow& _Window)
{
	_Window.draw(m_TileShape);
}