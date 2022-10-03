#include "UiManager.h"

UiManager::UiManager()
{
}


UiManager::~UiManager()
{
}

void UiManager::Update(sf::RenderWindow& _Window, int _CharacterHealth, bool _HasKey)
{
	//draw a blue box the size of the view
	sf::RectangleShape hudAreaBox;
	hudAreaBox.setSize(sf::Vector2f(1024, 64 * 2));
	hudAreaBox.setPosition(sf::Vector2f(-32, -32 - 64 * 2));
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

	//draw a box from the right to left for each health point
	for (int i = 0; i < _CharacterHealth; i++)
	{
		sf::RectangleShape HealthBar;
		HealthBar.setSize(sf::Vector2f(32, 32));
		HealthBar.setOrigin(HealthBar.getSize().x / 2, HealthBar.getSize().y / 2);
		//HealthBar.setPosition(sf::Vector2f(hudAreaBox.getGlobalBounds().width - (i * 32), hudAreaBox.getGlobalBounds().top));
		HealthBar.setPosition(sf::Vector2f(hudAreaBox.getGlobalBounds().width - (i * 64) - 64 * 2, hudAreaBox.getPosition().y + hudAreaBox.getGlobalBounds().height / 2));
		HealthBar.setFillColor(sf::Color::Red);
		_Window.draw(HealthBar);
	}

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



}
