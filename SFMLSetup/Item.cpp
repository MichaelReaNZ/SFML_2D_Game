#include "Item.h"

Item::Item(sf::Vector2f _Position)
{
	m_texture = new sf::Texture();
	m_texture->loadFromFile("Assets/Key.png");
	m_Shape.setTexture(m_texture);
	m_Shape.setSize(sf::Vector2f(64, 64));
	m_Shape.setOrigin(m_Shape.getSize().x / 2, m_Shape.getSize().y / 2);
	m_Shape.setPosition(_Position);
	m_Shape.setFillColor(sf::Color::Green);
}

Item::~Item()
{
	delete m_texture;
}

void Item::Update(sf::RenderWindow& _Window)
{
	_Window.draw(m_Shape);
}
