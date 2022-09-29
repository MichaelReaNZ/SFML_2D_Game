#include "Character.h"

Character::Character(Board* _Gameboard, sf::Vector2i _BoardPosition)
{
	m_Shape.setSize(sf::Vector2f(64, 64));

	m_CharacterBoardPosition = _BoardPosition;

	//Convert _BoardPosition to screen position
	sf::Vector2f screenPos = _Gameboard->BoardPositionToScreenPosition(m_CharacterBoardPosition);
	m_Shape.setPosition(screenPos);

	m_texture = new sf::Texture();
	m_texture->loadFromFile("Assets/Character.png");

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

	//if D move left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		boardOffset.x = 1;
	}

	//if A move right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		boardOffset.x = -1;
	}

	//if W move up
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		boardOffset.y = -1;
	}

	//if S move down
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		boardOffset.y = 1;
	}

	if (boardOffset.x != 0 || boardOffset.y != 0)
	{
		Move(boardOffset, _Gameboard);
	}
}

void Character::Move(sf::Vector2i _BoardOffset, Board* _Gameboard)
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
