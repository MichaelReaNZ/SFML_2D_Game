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

	float m_CharBaseSpeed = 6.0f;
	float m_CharSpeed = m_CharBaseSpeed;

	sf::Texture* m_texture;
	sf::Texture* m_AttackingTexture;



	sf::Clock m_invincibleTimeClock;
	bool m_IsInvincible = false;

	bool m_IsAttacking = false;

	sf::Sprite m_CharacterSprite;
	sf::RectangleShape m_WeaponBoundingBox;

	void Attack(Board* _Gameboard);
	void ReceiveDamageCollisions(Board* _Gameboard);

public:
	sf::RectangleShape m_Shape;
	sf::Vector2i m_CharacterBoardPosition;

	int m_health = 2;

	//bool colliding = false;
	//float playerVelocityY = 0.0f;

	//sf::RectangleShape* CharGetShape() { return m_Shape; }

	Character(sf::Vector2f _ScreenPosition);
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

