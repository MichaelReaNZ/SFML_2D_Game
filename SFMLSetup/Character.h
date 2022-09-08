#pragma once
#include "SFML/Graphics.hpp"
class Character
{
private:
	static const int moveAmount = 64;
	static const int divideMoveAmountBy = 1;



	sf::RectangleShape m_Shape; // the 2d image of the 
	sf::Texture* m_texture; // the texture of the 

public:
	sf::Vector2i m_CharacterBoardPosition;
	sf::Vector2i m_CharacterNextBoardPosition;
	bool m_CanMove = false;

	//offset vectors for each move
	sf::Vector2i m_BoardOffset;
	sf::Vector2f m_WorldOffset;

	Character(sf::Vector2f _Position);
	~Character();

	void Update(sf::RenderWindow& _Window);

	void CharacterInput();
	void Move(sf::Vector2f _OffsetVec, sf::Vector2i _boardOffset);
};

