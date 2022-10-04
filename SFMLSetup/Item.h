#pragma once
#include "SFML/Graphics.hpp"
#include "Enums.h"
class Item
{
	//sf::Vector2f m_Position;
	sf::Texture* m_texture;
public:


	sf::RectangleShape m_Shape;

	ItemType m_ItemType;
	Item(sf::Vector2f _Position, ItemType _ItemType);
	~Item();

	void Update(sf::RenderWindow& _Window);
};

