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
	const int frameLimit = 60;
	window.setFramerateLimit(frameLimit);


	Board* mainBoard = new Board();
	Character* mainCharacter = new Character(mainBoard->BoardPositionToScreenPosition(2, 3));

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



		//end level animation
		if (mainBoard->m_IsLevelComplete) {



			//if there are some rows left to black out
			if (deletingRowIndex >= 0) {

				//if there are some cols in that row to black out
				if (deletingColIndex >= 0) {
					mainBoard->m_tilePtrArray[deletingRowIndex][deletingColIndex]->m_TileSprite.setScale(0, 0);
					tilesBlackedOut++;
					deletingColIndex--;
					if (tilesBlackedOut <= 9000) {
						//slow it down and speed up as more tiles removed
						window.setFramerateLimit(tilesBlackedOut * 10 + frameLimit);
					}
				}
				else {
					//if there are no more cols in that row to black out go to next (prev) row
					deletingRowIndex--;
					//reset col index;
					deletingColIndex = n_rows - 1;
				}
			}
		}



		if (!uiManager.m_IsGameOver) {// && (tilesBlackedOut < n_cols * n_rows)) {
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