#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Character.h"
#include "Physics.h"
#include "Enemy.h"
#include "UiManager.h"


int main()
{
	//2 tile space for UI
	sf::RenderWindow window(sf::VideoMode(1024, 1024 + 64 * 2), "Tile Based Project");
	window.setFramerateLimit(60);

	UiManager uiManager = UiManager();
	Board* mainBoard = new Board();
	Character* mainCharacter = new Character(mainBoard->BoardPositionToScreenPosition(2, 2));


	//adding UI area 64
	//offset by half the tile size because of the tile center being the origin
	sf::View gameView(sf::FloatRect(-32, -32 - 64 * 2, 1024, 1024 + 64 * 2));

	//sf::View hudView(sf::FloatRect(0, 0, 1024, 0));


	while (window.isOpen())
	{
		if (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				//if (event.type == sf::Event::KeyPressed) {
				//	if (event.key.code == sf::Keyboard::Space) {
				//		//	mainCharacter->CharacterJump();
				//	}
				//}
			}
		}


		Physics physicsSystem;
		physicsSystem.PhysicsUpdate();
		physicsSystem.UpdateDynamicObject(mainCharacter, false);

		mainCharacter->CharacterInput(mainBoard);

		window.setView(gameView);
		window.clear();





		mainBoard->Update(window);
		mainCharacter->Update(window);






		//Draw HUD
		uiManager.Update(window, mainCharacter->m_health);

		window.display();
	}

	return 0;
}