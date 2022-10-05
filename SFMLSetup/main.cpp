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
	Character* mainCharacter = new Character(mainBoard->BoardPositionToScreenPosition(18, 19));

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


	//level 1 is in bottom right corner
	sf::View level1View(sf::FloatRect(1024 - 32, 1024 - (64 * 2) - 32, 1024, 1024 + (64 * 2)));
	//level 2 is in bottom left corner
	sf::View level2View(sf::FloatRect(0 - 32, 1024 - (64 * 2) - 32, 1024, 1024 + (64 * 2)));
	//level 3 is in top left corner
	sf::View level3View(sf::FloatRect(0 - 32, 0 - 32 - (64 * 2), 1024, 1024 + (64 * 2)));
	//level 4 is in top right corner
	sf::View level4View(sf::FloatRect(1024 - 32, 0 - 32 - (64 * 2), 1024, 1024 + (64 * 2)));
	//Set starting level view as level 1
	sf::View currentLevelView = level1View;

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

			sf::Vector2f charPos = mainCharacter->m_Shape.getPosition();

			//is character inside of levelView

			if (mainCharacter->m_HasKey) {
				//change to level if player is inside of that view
				if (mainCharacter->IsCharacterInsideLevelView(&level1View)) {
					currentLevelView = level1View;
				}
				else if (mainCharacter->IsCharacterInsideLevelView(&level2View)) {
					currentLevelView = level2View;
				}
				else if (mainCharacter->IsCharacterInsideLevelView(&level3View)) {
					currentLevelView = level3View;
				}
				else if (mainCharacter->IsCharacterInsideLevelView(&level4View)) {
					currentLevelView = level4View;
				}
			}




			window.setView(currentLevelView);
			window.clear();

			mainBoard->Update(window, currentLevelView);
			mainCharacter->Update(window);

			window.setView(gameView);
			uiManager.Update(window, mainCharacter->m_health, mainCharacter->m_HasKey);



			window.display();
		}

	}
	return 0;

}