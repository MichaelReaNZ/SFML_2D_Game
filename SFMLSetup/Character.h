#pragma once
#include "SFML/Graphics.hpp"
class Character
{
private:
	static const int moveAmount = 64;
	static const int divideMoveAmountBy = 8;

	sf::RectangleShape m_Shape; // the 2d image of the 
	sf::Texture* m_texture; // the texture of the 

public:
	sf::Vector2i m_BoardPosition;

	Character(sf::Vector2f _Position);
	~Character();

	void Update(sf::RenderWindow& _Window);

	void Move();
};

