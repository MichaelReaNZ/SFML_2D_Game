#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class MouseInput
{
public:
	bool m_LeftMouseDown = false;
	bool m_RightMouseDown = false;

	void MouseButtonInput();
};

