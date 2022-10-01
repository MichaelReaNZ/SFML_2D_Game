#include "Character.h"

Character::Character(Board* _Gameboard, sf::Vector2i _BoardPosition)
{
	m_CharactorPos = sf::Vector2f(130, 130);


	m_Shape.setSize(sf::Vector2f(64, 64));

	m_CharacterBoardPosition = _BoardPosition;

	//Convert _BoardPosition to screen position
	sf::Vector2f screenPos = _Gameboard->BoardPositionToScreenPosition(m_CharacterBoardPosition);
	m_Shape.setPosition(screenPos);
	//set to center
	m_Shape.setOrigin(m_Shape.getSize().x / 2, m_Shape.getSize().y / 2);

	m_texture = new sf::Texture();
	m_texture->loadFromFile("Assets/HeroCharacter.png");

	//set to red
	//m_Shape.setFillColor(sf::Color::Red);
	m_Shape.setTexture(m_texture);

}

Character::~Character()
{
	delete m_texture;
}

void Character::Update(sf::RenderWindow& _Window)
{
	_Window.draw(m_Shape);
}

void Character::CharacterInput(Board* _Gameboard) {
	sf::Vector2i boardOffset;

	//right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		boardOffset.x += 1;
	}

	//left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		boardOffset.x += -1;
	}

	//up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		boardOffset.y += -1;
	}

	//down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		boardOffset.y += 1;
	}

	m_CharMoveVec = boardOffset;

	if (boardOffset.x != 0 || boardOffset.y != 0)
	{
		//MoveToTile(boardOffset, _Gameboard);
		Move(1.0f, _Gameboard->m_WorldCollisionRects);
	}
}

void Character::Move(float _dt, std::vector<sf::FloatRect*> Collisions)
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


