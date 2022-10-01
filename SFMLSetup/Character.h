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

	sf::Vector2f m_CharactorPos;

	//can use this for direction
	sf::Vector2i m_CharMoveVec = sf::Vector2i(0, 0);

	float m_CharBaseSpeed = 5.0f;
	float m_CharSpeed = m_CharBaseSpeed;

	////remove this?
	//Direction m_direction;


	sf::Texture* m_texture; // the texture of the 

public:
	sf::RectangleShape m_Shape; // the 2d image of the 
	sf::Vector2i m_CharacterBoardPosition;

	bool colliding = false;
	//float playerVelocityY = 0.0f;

	//sf::RectangleShape* CharGetShape() { return m_Shape; }

	Character(Board* _Gameboard, sf::Vector2i _BoardPosition);
	~Character();

	//void Update(sf::RenderWindow& _Window);
	void Update(sf::RenderWindow& _Window);

	void CharacterInput(Board* gameboard);
	//void NewMove(sf::Vector2i _BoardOffset);
	void MoveToTile(sf::Vector2i _boardOffset, Board* gameboard);
	void Move(float _dt, std::vector<sf::FloatRect*> Collisions);

	//void CharacterJump() { m_Shape.move(0, -0.2f); playerVelocityY = -5.0f; }

	void modCharSpeed(float _valMod) { m_CharSpeed = _valMod * m_CharBaseSpeed; }

	//Bullet Shoot();
};

