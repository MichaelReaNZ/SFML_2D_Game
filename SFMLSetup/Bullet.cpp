#include "Bullet.h"


Bullet::Bullet(sf::Vector2f _Position, Direction _Direction)
{
	m_position = _Position;
	m_direction = _Direction;
	m_speed = 1;
}
