#pragma once
#include "SFML/Graphics.hpp"
#include "Character.h"
#include "Board.h"

class UiManager
{
public:
	UiManager();
	~UiManager();

	bool m_IsGameOver = false;

	//bool m_IsNewGame = true;

	void Update(sf::RenderWindow& _Window, int _CharacterHealth, bool _HasKey, int _Score, int _HighScore, sf::Clock _RunningTime, bool _IsGameComplete);
	void UpdateDebugWindow(sf::RenderWindow& _DebugWindow, Character* _Character, Board* _Board);
};

