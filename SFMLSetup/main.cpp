#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Character.h"
#include "Physics.h"
#include "Enemy.h"
#include "UiManager.h"


int main()
{
	UiManager uiManager = UiManager();

	//2 tile space for UI
	sf::RenderWindow window(sf::VideoMode(1024, 1024 + 64 * 2), "Tile Based Project");
	window.setFramerateLimit(40);


	Board* mainBoard = new Board();
	Character* mainCharacter = new Character(mainBoard->BoardPositionToScreenPosition(2, 3));

	//adding UI area 64
	//offset by half the tile size because of the tile center being the origin
	sf::View gameView(sf::FloatRect(-32, -32 - 64 * 2, 1024, 1024 + 64 * 2));


	Physics physicsSystem;

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();


			if (event.type == sf::Event::KeyPressed) {
				if (uiManager.m_IsGameOver) {
					if (event.key.code == sf::Keyboard::Enter) {
						//uiManager.m_IsNewGame = true;

						//set back to level 1 start
						delete mainCharacter;
						delete mainBoard;
						mainCharacter = new Character(mainBoard->BoardPositionToScreenPosition(2, 2));
						mainBoard = new Board();

						uiManager.m_IsGameOver = false;
					}
				}
			}
		}






		if (!uiManager.m_IsGameOver) {
			physicsSystem.PhysicsUpdate();
			physicsSystem.UpdateDynamicObject(mainCharacter, false);

			mainCharacter->CharacterInput(mainBoard);

			window.setView(gameView);
			window.clear();


			mainBoard->Update(window);
			mainCharacter->Update(window);
			uiManager.Update(window, mainCharacter->m_health, mainCharacter->m_HasKey);

			window.display();
		}

	}
	return 0;

}