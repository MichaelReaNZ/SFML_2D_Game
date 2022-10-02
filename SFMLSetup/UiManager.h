#pragma once
#include "SFML/Graphics.hpp"

class UiManager
{
public:
	UiManager();
	~UiManager();

	void Update(sf::RenderWindow& _Window, int _CharacterHealth);
};

