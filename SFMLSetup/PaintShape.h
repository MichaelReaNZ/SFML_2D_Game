#pragma once
#include "SFML/Graphics.hpp"

enum ShapeType {
	type_Circle,
	type_Rect
};

class PaintShape
{
	// the purpose of painshape is to help me draw shapes.

	// shape options: square / rectangle, circle. 
	// this class provides an interface for:
	// create the shape. 
	// choosing the shape.
	// rendering the shape.
	// updating the shape.
	// deleting the shape.
public: 
	PaintShape(sf::Vector2f _Position, ShapeType _Type);
	~PaintShape();
	void Render(sf::RenderWindow& _Window);
	void Update(sf::RenderWindow& _Window);
	sf::Shape* m_Shape;

private:
	
};

