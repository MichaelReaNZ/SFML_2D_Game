#include "Character.h"

Character::Character(sf::Vector2f _ScreenPosition)
{
	m_Shape.setSize(sf::Vector2f(64, 64));
	m_Shape.setPosition(_ScreenPosition);
	m_Shape.setOrigin(m_Shape.getSize().x / 2, m_Shape.getSize().y / 2);

	m_texture = new sf::Texture();
	m_texture->loadFromFile("Assets/HeroCharacter.png");

	m_CharacterSprite.setTexture(*m_texture);
	m_CharacterSprite.setOrigin(m_Shape.getOrigin());
	m_CharacterSprite.setPosition(m_Shape.getPosition());

	m_AttackingTexture = new sf::Texture();
	m_AttackingTexture->loadFromFile("Assets/HeroCharacterWithSword.png");

	//collision box for weapon
	m_WeaponBoundingBox.setSize(sf::Vector2f(64, 16));
	m_WeaponBoundingBox.setOrigin(m_WeaponBoundingBox.getSize().x / 2, m_WeaponBoundingBox.getSize().y / 2);
	m_WeaponBoundingBox.setPosition(sf::Vector2f(m_Shape.getPosition().x + m_Shape.getGlobalBounds().width, m_Shape.getPosition().y));
	m_WeaponBoundingBox.setFillColor(sf::Color::Magenta);
}

Character::~Character()
{
	delete m_texture;
}

void Character::Update(sf::RenderWindow& _Window)
{
	_Window.draw(m_Shape);
	_Window.draw(m_CharacterSprite);
	//for testing
	//_Window.draw(m_WeaponBoundingBox);
}

void Character::CharacterInput(Board* _Gameboard) {
	m_CharMoveVec.x = 0;
	m_CharMoveVec.y = 0;

	m_IsAttacking = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	//right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_CharMoveVec.x += 1;
	}

	//left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_CharMoveVec.x += -1;
	}

	//up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_CharMoveVec.y += -1;
	}

	//down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_CharMoveVec.y += 1;
	}


	Move(1.0f, _Gameboard->m_WorldCollisionRects);
	Attack(_Gameboard);
	ReceiveDamageCollisions(_Gameboard);
	ItemCollisions(_Gameboard);
}

void Character::Move(float _dt, std::vector<sf::FloatRect*> Collisions)
{
	if (m_CharMoveVec.x != 0 || m_CharMoveVec.y != 0)
	{
		m_CharMoveVec.x *= m_CharSpeed * _dt;
		m_CharMoveVec.y *= m_CharSpeed * _dt;

		//move x and y seperate to avoid glitchyness of being moved up when you have colided horizontally
		m_Shape.move(m_CharMoveVec.x, 0.00f);
		std::cout << "Movement x" << m_CharMoveVec.x << std::endl;

		for (int i = 0; i < Collisions.size(); i++) {
			{
				sf::FloatRect shapeBounds = m_Shape.getGlobalBounds();
				if (m_Shape.getGlobalBounds().intersects(*Collisions[i]))
				{
					Collisions::ResolveXCollisions(&m_Shape, Collisions[i]);
				}
			}
		}

		m_Shape.move(0.00f, m_CharMoveVec.y);
		std::cout << "Movement y" << m_CharMoveVec.y << std::endl;

		for (int i = 0; i < Collisions.size(); i++) {
			{
				sf::FloatRect shapeBounds = m_Shape.getGlobalBounds();
				if (m_Shape.getGlobalBounds().intersects(*Collisions[i]))
				{
					Collisions::ResolveYCollisions(&m_Shape, Collisions[i]);
				}
			}
		}

		//also move the character sprite
		m_CharacterSprite.setPosition(m_Shape.getPosition());

	}
}

void Character::MoveToTile(sf::Vector2i _BoardOffset, Board* _Gameboard)
{
	sf::Vector2i boardPositionToMoveTo = m_CharacterBoardPosition + _BoardOffset;

	std::cout << "Character attempting to move to Board Position: " << "x:" << boardPositionToMoveTo.x << ", " << "y:" << boardPositionToMoveTo.y << std::endl;

	if (_Gameboard->CanMoveToTile(boardPositionToMoveTo)) {
		m_CharacterBoardPosition = boardPositionToMoveTo;

		//calculate screen offset
		sf::Vector2f offSet;
		offSet.x = _BoardOffset.x * moveAmount;
		offSet.y = _BoardOffset.y * moveAmount;

		m_Shape.move(offSet);

		std::cout << "Character move success" << std::endl;
	}
	else {
		//TODO:Sound effect of can't move played
		std::cout << "Character move failed" << std::endl;
	}

	std::cout << "Character Board Position: x:" << m_CharacterBoardPosition.x << ", " << "y:" << m_CharacterBoardPosition.y << std::endl;
}

//Bullet Character::Shoot()
//{
//	return Bullet(m_Shape.getPosition(), m_direction);
//}

void Character::ReceiveDamageCollisions(Board* _Gameboard) {

	//Enemy damage collisions
	if (!m_IsInvincible) {
		for (int i = 0; i < _Gameboard->m_Enemies.size(); i++)
		{
			if (m_Shape.getGlobalBounds().intersects(_Gameboard->m_Enemies[i]->m_Shape.getGlobalBounds()))
			{
				std::cout << "Colliding with enemy." << std::endl;
				m_health -= 1;
				std::cout << "Reduced health to: " << m_health << std::endl;
				m_invincibleTimeClock.restart();
				m_IsInvincible = true;
				std::cout << "Invincible for 2 seconds." << std::endl;
				m_Shape.setFillColor(sf::Color::Red);
				m_CharacterSprite.setColor(sf::Color::Red);
			}
		}
	}

	if (m_IsInvincible && m_invincibleTimeClock.getElapsedTime().asSeconds() > 2) {
		m_IsInvincible = false;
		std::cout << "No longer Invincible." << std::endl;
		m_Shape.setFillColor(sf::Color::White);
		m_CharacterSprite.setColor(sf::Color::White);
	}
}

void Character::ItemCollisions(Board* _Gameboard) {
	for (int i = 0; i < _Gameboard->m_Items.size(); i++)
	{
		if (m_Shape.getGlobalBounds().intersects(_Gameboard->m_Items[i]->m_Shape.getGlobalBounds()))
		{
			if (_Gameboard->m_Items[i]->m_ItemType == KEY) {
				std::cout << "Colliding with key." << std::endl;
				m_HasKey = true;
				_Gameboard->m_Items.erase(_Gameboard->m_Items.begin() + i);
			}
			else if (_Gameboard->m_Items[i]->m_ItemType == DOOR) {
				if (m_HasKey) {
					std::cout << "Colliding with door." << std::endl;
					//TODO:Unlock door sound
					m_HasKey = false;
					//if character is the left of the door
					if (m_Shape.getPosition().x < _Gameboard->m_Items[i]->m_Shape.getPosition().x) {

						std::cout << "Have passed through door." << std::endl;
						//TODO:Move to next level
					}
				}
				else {
					Collisions::ResolveXCollisions(&m_Shape, new sf::FloatRect(_Gameboard->m_Items[i]->m_Shape.getGlobalBounds().left, _Gameboard->m_Items[i]->m_Shape.getGlobalBounds().top, _Gameboard->m_Items[i]->m_Shape.getGlobalBounds().width, _Gameboard->m_Items[i]->m_Shape.getGlobalBounds().height));
					std::cout << "Colliding with door but it's locked." << std::endl;
				}


				//take player to next level
			}
		}
	}
}

void Character::Attack(Board* _Gameboard) {
	//sword collisions
	if (m_IsAttacking) {
		std::cout << "Attacking." << std::endl;
		m_CharacterSprite.setTexture(*m_AttackingTexture, true);
		//move the weapon bounding box next to the character if attacking
		m_WeaponBoundingBox.setPosition(sf::Vector2f(m_Shape.getPosition().x + m_Shape.getGlobalBounds().width, m_Shape.getPosition().y));

		int numberOfEnemiesRemain = _Gameboard->m_Enemies.size();
		//check if the weapon bounding box is colliding with an enemy
		for (int i = 0; i < numberOfEnemiesRemain; i++)
		{
			//enemy death
			if (m_WeaponBoundingBox.getGlobalBounds().intersects(_Gameboard->m_Enemies[i]->m_Shape.getGlobalBounds()))
			{
				if (numberOfEnemiesRemain == 1) {
					//key 
					_Gameboard->SpawnKey();
				}

				std::cout << "Weapon is Colliding with enemy." << std::endl;

				//remove enemy from enemy array
				delete _Gameboard->m_Enemies[i];
				_Gameboard->m_Enemies.erase(_Gameboard->m_Enemies.begin() + i);

				//play enemy dead sound

				std::cout << "Enemy killed" << std::endl;
				//if that was the last enemy then drop the key in it's position.

			}
		}

	}
	else {
		m_CharacterSprite.setTexture(*m_texture, true);
		//move the weapon bounding box back to the character if not attacking
		m_WeaponBoundingBox.setPosition(sf::Vector2f(m_Shape.getPosition().x, m_Shape.getPosition().y));
	}
}
