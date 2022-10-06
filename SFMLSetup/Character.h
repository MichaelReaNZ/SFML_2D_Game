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

	//float m_CharBaseSpeed = 6.0f;


	sf::Texture* m_texture;
	sf::Texture* m_AttackingTexture;



	sf::Clock m_invincibleTimeClock;
	bool m_IsInvincible = false;
	bool m_IsAttacking = false;


	sf::Sprite m_CharacterSprite;
	sf::RectangleShape m_WeaponBoundingBox;

	void Attack(Board* _Gameboard);
	void ReceiveDamageCollisions(Board* _Gameboard);
	void ItemCollisions(Board* _Gameboard);

public:
	sf::RectangleShape m_Shape;
	float m_CharSpeed = 8.0f;

	int m_health = 3;
	bool m_HasKey = false;

	bool m_IsTransitioningLevels = false;

	Character(sf::Vector2f _ScreenPosition);
	~Character();

	void Update(sf::RenderWindow& _Window);

	void CharacterInput(Board* gameboard);
	void MoveToTile(sf::Vector2i _boardOffset, Board* gameboard);
	void Move(float _dt, std::vector<sf::FloatRect*> Collisions);
	bool IsCharacterInsideLevelView(sf::View* _LevelView);
};

