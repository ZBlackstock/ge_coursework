#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "event_man.hpp"
#include "input_man.hpp"

// make timer globally accessible and setable

using em = EventManager;

class Button;
std::shared_ptr<Button> em::_currentButton = nullptr;


std::shared_ptr<Button>  em::get_current_button()
{
	return em::_currentButton;
}

void em::set_current_button(std::shared_ptr<Button> button)
{
	// Set prev current button to idle sprite
	if (em::_currentButton)
	{
		em::_currentButton.get()->idle();
	}
	em::_currentButton = button;

	if (em::_currentButton)
	{
		em::_currentButton.get()->highlight();
	}
}

void em::clear_current_button()
{
	// Set prev current button to idle sprite
	if (em::_currentButton)
	{
		em::_currentButton = nullptr;
	}
}

void em::update(const float& dt)
{
	em::button_navigate_detect();

}

void em::button_navigate_detect()
{
	//Check for key up input
	if (InputManager::press_up())
	{
		//Check current selected button, and selected button above not null
		if (em::_currentButton && em::_currentButton->above)
		{
			//Set new button
			em::set_current_button(em::_currentButton.get()->above);
		}
	}

	//Check for key down input
	if (InputManager::press_down())
	{
		//Check current selected button, and selected button below not null
		if (em::_currentButton && em::_currentButton->below)
		{
			//Set new button
			em::set_current_button(em::_currentButton.get()->below);
		}
	}

	//Check for key left input
	if (InputManager::press_left())
	{
		//Check current selected button, and selected button left not null
		if (em::_currentButton && em::_currentButton->left)
		{
			//Set new button
			em::set_current_button(em::_currentButton.get()->left);
		}
	}

	//Check for right input
	if (InputManager::press_right())
	{
		//Check current selected button, and selected button right not null
		if (em::_currentButton && em::_currentButton->right)
		{
			//Set new button
			em::set_current_button(em::_currentButton.get()->right);
		}
	}

	if (InputManager::press_submit())
	{
		if (em::_currentButton)
		{
			em::_currentButton->on_select();
		}
	}
}
