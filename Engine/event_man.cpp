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
float em::wait_between_input = 0.25f; // To stop holding down keys spamming buttons
float em::input_wait_timer = em::wait_between_input;

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
	em::_currentButton.get()->highlight();

	std::cout << "current button = " << button.get()->get_name() << std::endl;
}

bool em::can_press_button()
{
	return em::input_wait_timer < 0;
}

void em::reset_input_timer()
{
	em::input_wait_timer = em::wait_between_input;
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
	//Timer stops accidental spamming
	if (em::input_wait_timer < 0)
	{
		em::input_wait_timer = -1.0f;
		em::button_navigate_detect();
	}

	em::input_wait_timer -= dt;
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
		em::input_wait_timer = em::wait_between_input;
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
		em::input_wait_timer = em::wait_between_input;
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
		em::input_wait_timer = em::wait_between_input;
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
		em::input_wait_timer = em::wait_between_input;
	}

	if (InputManager::press_submit())
	{
		if (em::_currentButton)
		{
			em::_currentButton->on_select();
		}
		em::input_wait_timer = em::wait_between_input;
	}
}
