#include "Item.h"

Item::Item(sf::Vector2f _Position, ItemType _ItemType)
{
	m_ItemType = _ItemType;
	m_texture = new sf::Texture();

	m_Shape.setSize(sf::Vector2f(64, 64));
	m_Shape.setOrigin(m_Shape.getSize().x / 2, m_Shape.getSize().y / 2);
	m_Shape.setPosition(_Position);

	switch (m_ItemType)
	{
	case ItemType::KEY:
	{
		m_texture->loadFromFile("Assets/Key.png");
		break;
	}
	case ItemType::DOOR:
	{
		m_Shape.setSize(sf::Vector2f(64, 128));
		m_Shape.setOrigin(m_Shape.getSize().x / 2, m_Shape.getSize().y / 2 / 2);
		m_texture->loadFromFile("Assets/Door.png");
		break;
	}
	}
	m_Shape.setTexture(m_texture);
}

Item::~Item()
{
	delete m_texture;
}

void Item::Update(sf::RenderWindow& _Window)
{
	_Window.draw(m_Shape);
}
