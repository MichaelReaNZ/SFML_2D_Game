#include "UiManager.h"


UiManager::UiManager()
{
}


UiManager::~UiManager()
{
}

void UiManager::Update(sf::RenderWindow& _Window, int _CharacterHealth, bool _HasKey, int _Score, int _HighScore, sf::Clock _RunningTime)
{
	sf::View view = _Window.getView();

	//draw a blue box the size of the view
	sf::RectangleShape hudAreaBox;
	//hudAreaBox.setSize(sf::Vector2f(1024, 64 * 2));
	hudAreaBox.setSize(sf::Vector2f(view.getSize().x, 64 * 2));

	//draw in same place no matter where the view is


	//hudAreaBox.setPosition(sf::Vector2f(view.getViewport().left * _Window.getSize().x, view.getViewport().top * _Window.getSize().y));
	//hudAreaBox.setPosition(sf::Vector2f((view.getCenter().x - view.getSize().x / 2) - 32, (view.getCenter().y - view.getSize().y / 2) - 32 - 64 * 2));
	hudAreaBox.setPosition(sf::Vector2f(view.getViewport().left - 32, view.getViewport().top - 32 - 64 * 2));
	hudAreaBox.setFillColor(sf::Color::Blue);

	//death screen
	if (_CharacterHealth <= 0) {
		m_IsGameOver = true;
		//draw white screen
		sf::RectangleShape deathScreen;
		deathScreen.setSize(sf::Vector2f(_Window.getSize().x, _Window.getSize().y));
		deathScreen.setPosition(hudAreaBox.getPosition());
		//	deathScreen.setFillColor(sf::Color::White);

		sf::Texture texture = sf::Texture();
		texture.loadFromFile("Assets/GameOverScreen.png");
		deathScreen.setTexture(&texture);

		//press enter to try again
		_Window.draw(deathScreen);
		return;
	}

	_Window.draw(hudAreaBox);

	sf::Texture* heartTexture = new sf::Texture();
	heartTexture->loadFromFile("Assets/Heart.png");

	//draw a box from the right to left for each health point
	for (int i = 0; i < _CharacterHealth; i++)
	{
		sf::RectangleShape HealthBar;
		HealthBar.setSize(sf::Vector2f(64, 64));
		HealthBar.setOrigin(HealthBar.getSize().x / 2, HealthBar.getSize().y / 2);
		//HealthBar.setPosition(sf::Vector2f(hudAreaBox.getGlobalBounds().width - (i * 32), hudAreaBox.getGlobalBounds().top));
		HealthBar.setPosition(sf::Vector2f(hudAreaBox.getGlobalBounds().width - (i * 64) - 64 * 2, hudAreaBox.getPosition().y + hudAreaBox.getGlobalBounds().height / 2));
		//HealthBar.setFillColor(sf::Color::Red);
		HealthBar.setTexture(heartTexture);
		_Window.draw(HealthBar);
	}
	delete heartTexture;

	//key
	if (_HasKey) {
		{
			//draw on the left side
			sf::Texture* keyTexture = new sf::Texture();
			keyTexture->loadFromFile("Assets/Key.png");
			sf::Sprite keySprite;
			keySprite.setTexture(*keyTexture);
			keySprite.setOrigin(keySprite.getGlobalBounds().left / 2, keySprite.getGlobalBounds().width / 2);
			keySprite.setPosition(sf::Vector2f(hudAreaBox.getGlobalBounds().left + 64, hudAreaBox.getPosition().y + hudAreaBox.getGlobalBounds().height / 2));
			_Window.draw(keySprite);
			delete keyTexture;
		}
	}

	//draw score
	sf::Font font;
	font.loadFromFile("Assets/font.ttf");
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("Score: " + std::to_string(_Score));
	scoreText.setCharacterSize(80);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(sf::Vector2f((hudAreaBox.getGlobalBounds().left / 2) + 64 * 3, (hudAreaBox.getPosition().y + hudAreaBox.getGlobalBounds().height / 2) - 64 - 32));
	_Window.draw(scoreText);


	sf::Text highScoreText;
	highScoreText.setFont(font);
	highScoreText.setString("High Score: " + std::to_string(_HighScore));
	highScoreText.setCharacterSize(80);
	highScoreText.setFillColor(sf::Color::White);
	highScoreText.setPosition(sf::Vector2f((hudAreaBox.getGlobalBounds().left / 2) + 64 * 3, (hudAreaBox.getPosition().y + hudAreaBox.getGlobalBounds().height / 2) - 32));
	_Window.draw(highScoreText);

	if (_RunningTime.getElapsedTime().asSeconds() < 15) {
		//down the very bottom tell the user to move with WASD keys
		sf::Text moveText;
		moveText.setFont(font);
		moveText.setString("Move with - WASD keys");
		moveText.setCharacterSize(84);
		moveText.setFillColor(sf::Color::White);
		moveText.setPosition(sf::Vector2f(hudAreaBox.getGlobalBounds().left + 64, view.getViewport().top + 1024 - 32 - 64 * 4));
		_Window.draw(moveText);

		moveText.setFont(font);
		moveText.setString("Attack with - Spacebar");
		moveText.setCharacterSize(84);
		moveText.setFillColor(sf::Color::White);
		moveText.setPosition(sf::Vector2f(hudAreaBox.getGlobalBounds().left + 64, view.getViewport().top + 1024 - 64 * 3));
		_Window.draw(moveText);
	}
}

void UiManager::UpdateDebugWindow(sf::RenderWindow& _DebugWindow, Character* _Character, Board* _Board)
{
	float width = _DebugWindow.getSize().x;
	float height = _DebugWindow.getSize().y;

	int howManyRows = 5;

	sf::Font font;
	font.loadFromFile("Assets/font.ttf");

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(58);
	text.setFillColor(sf::Color::Black);

	sf::Text textValue;
	textValue.setFont(font);
	textValue.setCharacterSize(58);
	textValue.setFillColor(sf::Color::Black);

	sf::Text minusText;
	minusText.setFont(font);
	minusText.setString("-");
	minusText.setCharacterSize(48);
	minusText.setFillColor(sf::Color::Black);

	sf::Text plusText;
	plusText.setFont(font);
	plusText.setString("+");
	plusText.setCharacterSize(48);
	plusText.setFillColor(sf::Color::Black);

	for (int i = 0; i < howManyRows; i++)
	{
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(width, height / howManyRows));
		rect.setFillColor(sf::Color::White);
		rect.setOutlineColor(sf::Color::Blue);
		rect.setOutlineThickness(5);
		rect.setPosition(sf::Vector2f(0, i * height / howManyRows));
		_DebugWindow.draw(rect);

		//draw a box on the left with a - symbol
		sf::RectangleShape rectMinus;
		rectMinus.setSize(sf::Vector2f(width / 5, height / howManyRows));
		rectMinus.setFillColor(sf::Color::Green);
		rectMinus.setOutlineColor(sf::Color::Blue);
		rectMinus.setOutlineThickness(1);
		rectMinus.setPosition(sf::Vector2f(0, (i * (height / howManyRows))));
		_DebugWindow.draw(rectMinus);

		//draw the - text in the middle of the rectMinus
		minusText.setPosition(sf::Vector2f(width / 10, (i * height / howManyRows) + (height / howManyRows) / 2));
		_DebugWindow.draw(minusText);

		//draw a box on the right with a + symbol
		sf::RectangleShape rectPlus;
		rectPlus.setSize(sf::Vector2f(width / 5, height / howManyRows));
		rectPlus.setFillColor(sf::Color::Green);
		rectPlus.setOutlineColor(sf::Color::Blue);
		rectPlus.setOutlineThickness(1);
		rectPlus.setPosition(sf::Vector2f(width - (width / 5), (i * height / howManyRows)));
		_DebugWindow.draw(rectPlus);

		//draw the + text
		plusText.setPosition(sf::Vector2f(width - (width / 10), (i * height / howManyRows) + (height / howManyRows) / 2));
		_DebugWindow.draw(plusText);

		//fill the first one with the text player speed
		if (i == 0)
		{
			text.setString("Player Speed: ");
			textValue.setString(std::to_string(_Character->m_CharSpeed));
		}

		if (i == 1)
		{
			text.setString("Score: ");
			textValue.setString(std::to_string(_Board->m_Score));
		}
		if (i == 2)
		{
			text.setString("Health: ");
			textValue.setString(std::to_string(_Character->m_health));
		}
		if (i == 3)
		{
			text.setString("Enemy Move Speed: ");
			textValue.setString(std::to_string(_Board->m_EnemyMoveSpeed));
		}
		if (i == 4)
		{
			text.setString("Enemy Shoot Speed: ");
			textValue.setString(std::to_string(_Board->m_EnemyShootSpeed));
		}

		//positioned in the middle of the rect
		text.setPosition(sf::Vector2f((width / 2 - textValue.getGlobalBounds().width / 2) - 32, i * height / howManyRows + height / howManyRows / (2 - textValue.getGlobalBounds().height / 2)));
		_DebugWindow.draw(textValue);
		textValue.setPosition(sf::Vector2f((width / 2 - textValue.getGlobalBounds().width / 2) - 32, i * height / howManyRows + height / howManyRows / (2 - textValue.getGlobalBounds().height / 2 + 32)));
		_DebugWindow.draw(text);


		//if rectplus is clicked with the mouse increment value
		if (rectPlus.getGlobalBounds().contains(sf::Mouse::getPosition(_DebugWindow).x, sf::Mouse::getPosition(_DebugWindow).y))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (i == 0)
				{
					_Character->m_CharSpeed += 0.5f;
				}
				if (i == 1)
				{
					_Board->m_Score += 1;
				}
				if (i == 2)
				{
					_Character->m_health += 1;
				}
				if (i == 3)
				{
					_Board->m_EnemyMoveSpeed += 1.0f;
					//for each enemy set move speed
					for (int i = 0; i < _Board->m_Enemies.size(); i++)
					{
						_Board->m_Enemies[i]->m_MoveSpeed = _Board->m_EnemyMoveSpeed;
					}
				}
				if (i == 4)
				{
					_Board->m_EnemyShootSpeed += 1.0f;
					//for each enemy set shoot speed
					for (int i = 0; i < _Board->m_Enemies.size(); i++)
					{
						_Board->m_Enemies[i]->m_ShootSpeed = _Board->m_EnemyShootSpeed;
					}
				}

			}
		}

		//if rectMinus is clicked with the mouse decrement value
		if (rectMinus.getGlobalBounds().contains(sf::Mouse::getPosition(_DebugWindow).x, sf::Mouse::getPosition(_DebugWindow).y))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (i == 0)
				{
					_Character->m_CharSpeed -= 0.5f;
				}
				if (i == 1)
				{
					_Board->m_Score -= 1;
				}
				if (i == 2)
				{
					_Character->m_health -= 1;
				}
				if (i == 3)
				{
					_Board->m_EnemyMoveSpeed -= 1.0f;
					//for each enemy set move speed
					for (int i = 0; i < _Board->m_Enemies.size(); i++)
					{
						_Board->m_Enemies[i]->m_MoveSpeed = _Board->m_EnemyMoveSpeed;
					}
				}
				if (i == 4)
				{
					_Board->m_EnemyShootSpeed -= 1.0f;
					//for each enemy set shoot speed
					for (int i = 0; i < _Board->m_Enemies.size(); i++)
					{
						_Board->m_Enemies[i]->m_ShootSpeed = _Board->m_EnemyShootSpeed;
					}
				}
			}
		}






	}
}