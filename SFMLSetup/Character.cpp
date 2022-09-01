#include "Character.h"

Character::Character(sf::Vector2f _Position)
{
	m_Shape.setSize(sf::Vector2f(64, 64));
	m_Shape.setPosition(_Position);

	m_texture = new sf::Texture();
	m_texture->loadFromFile("Assets/Character.png");

	//set to red
	m_Shape.setFillColor(sf::Color::Red);
	//m_Shape.setTexture(m_texture);
}

Character::~Character()
{
	delete m_texture;
}

void Character::Update(sf::RenderWindow& _Window)
{
	_Window.draw(m_Shape);
}

void Character::Move()
{
	sf::Vector2f offsetVector;
	sf::Vector2i boardOffset;

	//if D move left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		float increment = moveAmount / divideMoveAmountBy;
		offsetVector.x = increment;
		boardOffset.x = 1;
	}

	//if A move right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		float increment = -moveAmount / divideMoveAmountBy;
		offsetVector.x = increment;
		boardOffset.x = -1;
	}

	//if W move up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		float increment = -moveAmount / divideMoveAmountBy;
		offsetVector.y = increment;
		boardOffset.y = -1;
	}

	//if S move down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		float increment = moveAmount / divideMoveAmountBy;
		offsetVector.y = increment;
		boardOffset.y = 1;
	}


	m_Shape.move(offsetVector);
	m_BoardPosition = m_BoardPosition + boardOffset;

}
