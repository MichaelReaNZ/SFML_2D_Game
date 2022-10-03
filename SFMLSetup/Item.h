#pragma once
#include "SFML/Graphics.hpp"
class Item
{
	//sf::Vector2f m_Position;
	sf::Texture* m_texture;
public:
	sf::RectangleShape m_Shape;

	Item(sf::Vector2f _Position);
	~Item();

	void Update(sf::RenderWindow& _Window);
};

