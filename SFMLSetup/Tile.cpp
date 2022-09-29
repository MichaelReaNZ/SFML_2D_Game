#include "Tile.h"

Tile::Tile(sf::Vector2f _Position, TileType _Type, sf::Texture* _Texture)
{
	//Shape is to show outline only
	m_TileShape.setSize(sf::Vector2f(64, 64));
	m_TileShape.setOrigin(m_TileShape.getSize().x / 2, m_TileShape.getSize().y / 2);
	m_TileShape.setPosition(_Position);
	m_TileShape.setOutlineColor(sf::Color::Blue);
	m_TileShape.setOutlineThickness(4);

	//Sprite is more performace effecient
	m_TileSprite.setTexture(*_Texture);
	m_TileSprite.setPosition(_Position);
	m_TileSprite.setOrigin(m_TileSprite.getGlobalBounds().width / 2, m_TileSprite.getGlobalBounds().height / 2);

	m_TileType = _Type;
}

Tile::~Tile()
{
	//delete m_texture;
}

void Tile::Update(sf::RenderWindow& _Window)
{
	_Window.draw(m_TileSprite);

	//This introduces performance issues
	//_Window.draw(m_TileShape);
}