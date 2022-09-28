#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Character.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 1024), "Tile Based Project");
	window.setFramerateLimit(120);

	Board* mainBoard = new Board();
	Character* mainCharacter = new Character(mainBoard, sf::Vector2i(3, 4));

	while (window.isOpen())
	{
		if (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::KeyPressed) {
					mainCharacter->CharacterInput(mainBoard);
				}
			}
		}
		window.clear();

		//TODO:Investigate performance issue with the map
		mainBoard->Update(window);
		mainCharacter->Update(window);

		window.display();
	}

	return 0;
}