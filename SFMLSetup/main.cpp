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
	const int frameLimit = 30;
	window.setFramerateLimit(frameLimit);

	//debug window
	bool debugWindowIsVisible = false;
	sf::RenderWindow debugWindow(sf::VideoMode(window.getSize().x / 2, window.getSize().y), "Debug Window");
	debugWindow.setPosition(sf::Vector2i(window.getPosition().x + window.getSize().x, window.getPosition().y));
	debugWindow.setVisible(debugWindowIsVisible);

	Board* mainBoard = new Board();
	Character* mainCharacter = new Character(mainBoard->BoardPositionToScreenPosition(19, 19));




	//adding UI area 64
	//offset by half the tile size because of the tile center being the origin
	sf::View gameView(sf::FloatRect(-32, -32 - 64 * 2, 1024, 1024 + 64 * 2));
	Physics physicsSystem;

	//level end animation remove each tile
	//get size
	int n_rows = sizeof(mainBoard->m_tilePtrArray) / sizeof(mainBoard->m_tilePtrArray[0]);
	int n_cols = sizeof(mainBoard->m_tilePtrArray[0]) / sizeof(mainBoard->m_tilePtrArray[0][0]);
	int deletingRowIndex = n_rows - 1;
	int deletingColIndex = n_cols - 1;
	int tilesBlackedOut = 0;


	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();


			if (event.type == sf::Event::KeyPressed) {
				if (uiManager.m_IsGameOver || mainBoard->m_IsGameComplete) {
					if (event.key.code == sf::Keyboard::Enter) {
						//set back to level 1 start
						delete mainCharacter;
						delete mainBoard;
						mainBoard = new Board();
						mainCharacter = new Character(mainBoard->BoardPositionToScreenPosition(19, 19));
						uiManager.m_IsGameOver = false;
						mainBoard->m_IsGameComplete = false;
					}
				}
				//esc key
				if (event.key.code == sf::Keyboard::Escape) {
					debugWindowIsVisible = !debugWindowIsVisible;
					debugWindow.setVisible(debugWindowIsVisible);
					uiManager.UpdateDebugWindow(debugWindow, mainCharacter, mainBoard);
					debugWindow.display();
				}
			}
		}



		//end level animation
		if (mainBoard->m_IsGameComplete) {
			//if there are some rows left to black out
			if (deletingRowIndex >= 0) {

				//if there are some cols in that row to black out

				if (deletingColIndex >= 0) {
					mainBoard->m_tilePtrArray[deletingRowIndex][deletingColIndex]->m_TileSprite.setScale(0, 0);
					tilesBlackedOut++;
					deletingColIndex--;
				}
				else {
					//if there are no more cols in that row to black out go to next (prev) row
					deletingRowIndex--;
					//reset col index;
					deletingColIndex = n_rows - 1;
				}
			}
		}

		if (!uiManager.m_IsGameOver) {
			physicsSystem.PhysicsUpdate();
			physicsSystem.UpdateDynamicObject(mainCharacter, false);

			mainCharacter->CharacterInput(mainBoard);
			mainBoard->EnemyMovement();
			mainBoard->EnemyAttack(mainCharacter->m_Shape.getPosition());

			//sf::Vector2f charPos = mainCharacter->m_Shape.getPosition();

			mainBoard->TransitionLevel(mainCharacter->m_Shape.getPosition());
			mainCharacter->m_IsTransitioningLevels = false;

			window.setView(*(mainBoard->m_CurrentLevelView));
			window.clear();

			mainBoard->Update(window, mainBoard->m_CurrentLevelView);
			mainCharacter->Update(window);

			window.setView(gameView);
			uiManager.Update(window, mainCharacter->m_health, mainCharacter->m_HasKey, mainBoard->m_Score, mainBoard->m_HighScore, mainBoard->m_TimeSinceGameStart, mainBoard->m_IsGameComplete);
			if (debugWindowIsVisible) {

				//only update when changing values
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					//debugWindow.clear();
					uiManager.UpdateDebugWindow(debugWindow, mainCharacter, mainBoard);
					debugWindow.display();
				}
			}
			window.display();
		}

	}
	return 0;

}