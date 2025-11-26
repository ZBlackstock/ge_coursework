#include "input_man.hpp"
#include <iostream>

const int InputManager::gamepad_a = 0; // Submit
const int InputManager::gamepad_b = 1; // Back
const int InputManager::gamepad_start = 7; // Menu
int InputManager::lstick_x = 0;
int InputManager::lstick_y = 1;
float InputManager::dpad_x = 0;
float InputManager::dpad_y = 0;
const float InputManager::dpad_dead = 0.1f;


void InputManager::Update(const float& dt)
{
	// Timer stuff

	dpad_x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX);
	dpad_y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY);
}

bool InputManager::press_submit()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)
		|| (InputManager::gamepad_connected &&
			sf::Joystick::isButtonPressed(0, InputManager::gamepad_a));
}

bool InputManager::press_back()
{
	return (InputManager::gamepad_connected &&
		sf::Joystick::isButtonPressed(0, InputManager::gamepad_b));
}

bool InputManager::press_menu()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
		|| (InputManager::gamepad_connected &&
			sf::Joystick::isButtonPressed(0, InputManager::gamepad_start));
}

bool InputManager::press_up()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		|| (InputManager::gamepad_connected &&
			dpad_y > dpad_dead);
}

bool InputManager::press_down()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		|| (InputManager::gamepad_connected &&
			dpad_y < -dpad_dead);
}

bool InputManager::press_left()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		|| (InputManager::gamepad_connected &&
			dpad_x < -dpad_dead);
}

bool InputManager::press_right()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		|| (InputManager::gamepad_connected &&
			dpad_x > dpad_dead);
}

bool InputManager::gamepad_connected()
{
	return sf::Joystick::isConnected(0);
}