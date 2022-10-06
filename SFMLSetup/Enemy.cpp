#include "Enemy.h"
#include "Board.h"

Enemy::Enemy(sf::Vector2f _Position)
{
	m_Shape.setSize(sf::Vector2f(64, 64));
	m_Shape.setPosition(_Position);
	m_Shape.setOrigin(m_Shape.getSize().x / 2, m_Shape.getSize().y / 2);

	m_texture = new sf::Texture();
	m_texture->loadFromFile("Assets/Enemy01.png");
	m_Shape.setTexture(m_texture);

	m_WalkingTimeClock.restart();
	ChangeDirectionRandomly();

	//random number between 1 and 3
	m_ShootFrequency = rand() % 3 + 1;
}

Enemy::~Enemy()
{
	delete m_texture;
}

void Enemy::Update(sf::RenderWindow& _Window)
{
	_Window.draw(m_Shape);
}

void Enemy::ChangeDirectionRandomly() {
	m_MoveVec.x = 0;
	m_MoveVec.y = 0;
	int randomDirection = rand() % 4 + 1;
	if (randomDirection == 1) {
		m_MoveVec.x += -m_MoveSpeed;
	}
	else if (randomDirection == 2) {
		m_MoveVec.x += m_MoveSpeed;
	}
	else if (randomDirection == 3) {
		m_MoveVec.y += -m_MoveSpeed;
	}
	else if (randomDirection == 4) {
		m_MoveVec.y += m_MoveSpeed;
	}
}

Bullet* Enemy::ShootBullet(sf::Vector2f _EnemyPosition, sf::Vector2f _CharacterPosition) {
	sf::Vector2i moveVector = sf::Vector2i(0, 0);

	//calculate the unit vector
	float x = _CharacterPosition.x - _EnemyPosition.x;
	float y = _CharacterPosition.y - _EnemyPosition.y;
	float length = sqrt(x * x + y * y);
	x = x / length;
	y = y / length;

	//calculate the move vector
	moveVector.x = x * m_ShootSpeed;
	moveVector.y = y * m_ShootSpeed;

	//create the bullet
	return new Bullet(_EnemyPosition, moveVector);
}

