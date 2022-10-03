#pragma once
#include "SFML/Graphics.hpp"

class UiManager
{
public:
	UiManager();
	~UiManager();

	bool m_IsGameOver = false;
	//bool m_IsNewGame = true;

	void Update(sf::RenderWindow& _Window, int _CharacterHealth);
};

