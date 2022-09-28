#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Character.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Tile Based Project");
	window.setFramerateLimit(60);

	Board* mainBoard = new Board(8, 8);
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

		mainBoard->Update(window);
		mainCharacter->Update(window);

		window.display();
	}

	return 0;
}