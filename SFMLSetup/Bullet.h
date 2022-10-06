#pragma once
#include "SFML/Graphics.hpp"
#include "Enums.h"

class Bullet
{
	int m_speed;
	sf::Vector2f  m_Position;

public:
	sf::CircleShape m_Shape;
	sf::Vector2i m_MoveVec = sf::Vector2i(0, 0);

	Bullet(sf::Vector2f _Position, sf::Vector2i _MoveVect);

	void Update(sf::RenderWindow& _Window);
};

