#include "Bullet.h"


Bullet::Bullet(sf::Vector2f _Position, sf::Vector2i _MoveVect)
{
	m_Position = _Position;
	m_MoveVec = _MoveVect;
	m_speed = 2;

	m_Shape = sf::CircleShape(10);
	m_Shape.setFillColor(sf::Color::Red);
	m_Shape.setPosition(m_Position);

}

void Bullet::Update(sf::RenderWindow& _Window)
{
	_Window.draw(m_Shape);
}
