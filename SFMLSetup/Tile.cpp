#include "Tile.h"

Tile::Tile(sf::Vector2f _Position, TileType _Type, sf::Texture* _Texture)
{
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
}