#include "PaintShape.h"

PaintShape::PaintShape(sf::Vector2f _Position, ShapeType _Type)
{
	switch (_Type)
	{
	case type_Circle: {
		sf::CircleShape* tempShape = new sf::CircleShape();
		tempShape->setRadius(10.0f);
		tempShape->setOrigin(tempShape->getRadius(), tempShape->getRadius());
		m_Shape = tempShape; }
			break;
	
	case type_Rect: {
		sf::RectangleShape* rectShape = new sf::RectangleShape();
		rectShape->setSize(sf::Vector2f(20, 20));
		rectShape->setOrigin(rectShape->getSize().x / 2, rectShape->getSize().y / 2);
		m_Shape = rectShape; }
			break;

		default:
			break;
	}

	m_Shape->setPosition(_Position);
	m_Shape->setFillColor(sf::Color::Cyan);
	m_Shape->setOutlineColor(sf::Color::Red);
	m_Shape->setOutlineThickness(3.0f);
}

PaintShape::~PaintShape()
{

}

void PaintShape::Render(sf::RenderWindow& _window)
{
	_window.draw(*m_Shape);
}

void PaintShape::Update(sf::RenderWindow& _window)
{

}
