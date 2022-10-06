#pragma once
#include "SFML/Graphics.hpp"

class Collisions
{
public:
	static void ResolveXCollisions(sf::Shape* _objA, sf::FloatRect* _objB) {
		sf::Vector2f entityACenter{ (_objA->getGlobalBounds().left + _objA->getGlobalBounds().width / 2.0f),
											(_objA->getGlobalBounds().top + _objA->getGlobalBounds().height / 2.0f) };

		sf::Vector2f entityBCenter{ (_objB->left + _objB->width / 2.0f),
											(_objB->top + _objB->height / 2.0f) };

		//if A is to the left of B then move back to the left
		if (entityACenter.x <= entityBCenter.x)
		{
			std::cout << "A is coliding to the left of B" << std::endl;
			float offset = -(_objA->getGlobalBounds().left + _objA->getGlobalBounds().width - _objB->left);
			_objA->move(offset, 0.0f);
			std::cout << "Collision resolved by moving A to the left by: " << offset << std::endl;
		}

		//if A is to the right of B then move back to the right
		if (entityACenter.x >= entityBCenter.x) {
			std::cout << "A is coliding to the right of B" << std::endl;
			float offset = ((_objB->left + _objB->width) - _objA->getGlobalBounds().left);
			_objA->move(offset, 0.00f);
			std::cout << "Collision resolved by moving A to the right by: " << offset << std::endl;
		}
	}

	static void ResolveYCollisions(sf::Shape* _pObjA, sf::FloatRect* _pObjB) {
		{
			sf::Vector2f entityACenter{ (_pObjA->getGlobalBounds().left + _pObjA->getGlobalBounds().width / 2.0f),
												(_pObjA->getGlobalBounds().top + _pObjA->getGlobalBounds().height / 2.0f) };

			sf::Vector2f entityBCenter{ (_pObjB->left + _pObjB->width / 2.0f),
												(_pObjB->top + _pObjB->height / 2.0f) };

			//if A is above B then move back up
			if (entityACenter.y <= entityBCenter.y)
			{
				std::cout << "A is coliding above B" << std::endl;
				float offset = -(_pObjA->getGlobalBounds().top + _pObjA->getGlobalBounds().height - _pObjB->top);
				_pObjA->move(0.0f, offset);
				std::cout << "Collision resolved by moving A up by: " << offset << std::endl;
			}

			//if A is below B then move back down
			if (entityACenter.y >= entityBCenter.y) {
				std::cout << "A is coliding below B" << std::endl;
				float offset = ((_pObjB->top + _pObjB->height) - _pObjA->getGlobalBounds().top);
				_pObjA->move(0.0f, offset);
				std::cout << "Collision resolved by moving A down by: " << offset << std::endl;
			}
		}
	}
};

//is position inside of levelView
static bool IsPositionInsideView(sf::View* _LevelView, sf::Vector2f _Position) {
	sf::Vector2f viewCenter = _LevelView->getCenter();
	sf::Vector2f viewSize = _LevelView->getSize();

	if (_Position.x > (viewCenter.x - viewSize.x / 2)
		&& _Position.x < (viewCenter.x + viewSize.x / 2)
		&& _Position.y >(viewCenter.y - viewSize.y / 2)
		&& _Position.y < (viewCenter.y + viewSize.y / 2)) {
		return true;
	}
	else { return false; }
}
