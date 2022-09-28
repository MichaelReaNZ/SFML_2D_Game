#pragma once
#include "SFML/Graphics.hpp"
#include "Board.h"
class Character
{
private:
	static const int moveAmount = 64;
	static const int divideMoveAmountBy = 1;

	sf::RectangleShape m_Shape; // the 2d image of the 
	sf::Texture* m_texture; // the texture of the 

public:
	sf::Vector2i m_CharacterBoardPosition;

	Character(Board* _Gameboard, sf::Vector2i _BoardPosition);
	~Character();

	void Update(sf::RenderWindow& _Window);

	void CharacterInput(Board* gameboard);

	void Move(sf::Vector2f _OffsetVec, sf::Vector2i _boardOffset, Board* gameboard);
};

