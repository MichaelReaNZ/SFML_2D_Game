#include "Enemy.h"

Enemy::Enemy(sf::Vector2f _Position)
{
	m_Shape.setSize(sf::Vector2f(64, 64));
	m_Shape.setPosition(_Position);
	//set to center
	m_Shape.setOrigin(m_Shape.getSize().x / 2, m_Shape.getSize().y / 2);

	m_texture = new sf::Texture();
	m_texture->loadFromFile("Assets/Enemy01.png");
	m_Shape.setTexture(m_texture);



}

Enemy::~Enemy()
{
	delete m_texture;
}

void Enemy::Update(sf::RenderWindow& _Window)
{
	_Window.draw(m_Shape);
}
