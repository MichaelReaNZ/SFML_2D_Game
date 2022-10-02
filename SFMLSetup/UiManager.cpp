#include "UiManager.h"

UiManager::UiManager()
{
}


UiManager::~UiManager()
{
}

void UiManager::Update(sf::RenderWindow& _Window, int _CharacterHealth)
{
	//draw a blue box the size of the view
	sf::RectangleShape hudAreaBox;
	hudAreaBox.setSize(sf::Vector2f(1024, 64 * 2));
	hudAreaBox.setPosition(sf::Vector2f(-32, -32 - 64 * 2));
	hudAreaBox.setFillColor(sf::Color::Blue);

	_Window.draw(hudAreaBox);

	//draw a box from the right to left for each health point
	for (int i = 0; i < _CharacterHealth; i++)
	{
		sf::RectangleShape HealthBar;
		HealthBar.setSize(sf::Vector2f(32, 32));
		//HealthBar.setPosition(sf::Vector2f(hudAreaBox.getGlobalBounds().width - (i * 32), hudAreaBox.getGlobalBounds().top));
		HealthBar.setPosition(sf::Vector2f(hudAreaBox.getGlobalBounds().width - (i * 64) - 64 * 2, hudAreaBox.getPosition().y + hudAreaBox.getGlobalBounds().height / 2));
		HealthBar.setFillColor(sf::Color::Red);
		_Window.draw(HealthBar);
	}


}
