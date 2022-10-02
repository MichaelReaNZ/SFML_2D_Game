#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Character.h"
#include "Physics.h"
#include "Enemy.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 1024), "Tile Based Project");
	window.setFramerateLimit(60);

	Board* mainBoard = new Board();
	Character* mainCharacter = new Character(mainBoard->BoardPositionToScreenPosition(2, 2));



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

		window.clear();

		//TODO:Investigate performance issue with the map
		mainBoard->Update(window);
		mainCharacter->Update(window);
		//mainEnemy->Update(window);

		window.display();
	}

	return 0;
}