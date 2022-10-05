#pragma once
#include "SFML/Graphics.hpp"

class Enemy
{
	sf::Vector2f m_Position;
	sf::Texture* m_texture;
public:
	sf::RectangleShape m_Shape;

	float m_MoveSpeed = 6.0f;
	float m_ShootSpeed = 6.0f;

	Enemy(sf::Vector2f _Position);
	~Enemy();
	void Update(sf::RenderWindow& _Window);


};

