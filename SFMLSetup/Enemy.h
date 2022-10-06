#pragma once
#include "SFML/Graphics.hpp"

class Enemy
{
	sf::Vector2f m_Position;
	sf::Texture* m_texture;
public:
	sf::RectangleShape m_Shape;

	float m_MoveSpeed = 6.0f;
	sf::Vector2i m_MoveVec = sf::Vector2i(0, 0);
	float m_ShootSpeed = 6.0f;

	sf::Clock m_WalkingTimeClock;
	//Direction m_MoveDirection;

	void ChangeDirectionRandomly();

	Enemy(sf::Vector2f _Position);
	~Enemy();
	void Update(sf::RenderWindow& _Window);

};

