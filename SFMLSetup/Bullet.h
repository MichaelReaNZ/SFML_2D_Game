#pragma once
#include "SFML/Graphics.hpp"
#include "Enums.h"

class Bullet
{	//direction
	//enum Direction { Up, Down, Left, Right };

	Direction m_direction;
	int m_speed;

	sf::Vector2f  m_position;

	//shape
	sf::RectangleShape m_bulletShape;
	sf::Texture* m_bulletTexture;



public:
	Bullet(sf::Vector2f _Position, Direction _Direction);

};

