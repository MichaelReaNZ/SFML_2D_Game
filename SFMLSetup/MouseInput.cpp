#include "MouseInput.h"

void MouseInput::MouseButtonInput()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_LeftMouseDown = true;
	}
	else
	{
		if (m_LeftMouseDown == true)
		{
			// lmb released.
			std::cout << "left mouse button released." << std::endl;
			m_LeftMouseDown = false;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		m_RightMouseDown = true;
	}
	else
	{
		if (m_RightMouseDown == true)
		{
			// rmb released.
			std::cout << "right mouse button released." << std::endl;
			m_RightMouseDown = false;
		}
	}

}
