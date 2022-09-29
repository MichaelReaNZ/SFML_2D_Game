#pragma once
#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Enums.h"
#include "Bullet.h"

#include "Collisions.h"

class Character
{
private:
	static const int moveAmount = 64;
	static const int divideMoveAmountBy = 1;

	//new stuff
	sf::Vector2f m_CharactorPos;
	//can use this for direction
	sf::Vector2i m_CharMoveVec = sf::Vector2i(0, 0);
	//sf::Vector2f m_CharMoveVec = sf::Vector2f(0.0f, 0.0f);
	float m_CharSpeed = 10.f;
	float m_CharBaseSpeed = 10.f;
	//new stuff

	//remove this?
	Direction m_direction;


	sf::Texture* m_texture; // the texture of the 

public:
	sf::RectangleShape m_Shape; // the 2d image of the 
	sf::Vector2i m_CharacterBoardPosition;

	bool colliding = false;
	float playerVelocityY = 0.0f;

	//sf::RectangleShape* CharGetShape() { return m_Shape; }

	Character(Board* _Gameboard, sf::Vector2i _BoardPosition);
	~Character();

	//void Update(sf::RenderWindow& _Window);
	void Update(sf::RenderWindow& _Window);

	void CharacterInput(Board* gameboard);
	//void NewMove(sf::Vector2i _BoardOffset);
	void Move(sf::Vector2i _boardOffset, Board* gameboard);
	void NewMove(float _dt, std::vector<sf::FloatRect*> Collisions);

	void CharacterJump() { m_Shape.move(0, -0.2f); playerVelocityY = -5.0f; }

	void modCharSpeed(float _valMod) { m_CharSpeed = _valMod * m_CharBaseSpeed; }

	//Bullet Shoot();
};

