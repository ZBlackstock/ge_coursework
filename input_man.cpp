#include "input_man.hpp"
#include <iostream>

using im = InputManager;
const int im::gamepad_a = 0; // Submit
const int im::gamepad_b = 1; // Back
const int im::gamepad_start = 7; // Menu
int im::lstick_x = 0;
int im::lstick_y = 1;
float im::dpad_x = 0;
float im::dpad_y = 0;
const float im::dpad_dead = 0.1f;
float im::wait_between_input = 0.25f; // To stop holding down keys spamming buttons
float im::input_wait_timer = im::wait_between_input;

sf::Keyboard::Key im::submit = sf::Keyboard::Space;
sf::Keyboard::Key im::up = sf::Keyboard::Up;
sf::Keyboard::Key im::down = sf::Keyboard::Down;
sf::Keyboard::Key im::left = sf::Keyboard::Left;
sf::Keyboard::Key im::right = sf::Keyboard::Right;

void im::Update(const float& dt)
{
	im::dpad_x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX);
	im::dpad_y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY);

	//Timer stops accidental spamming
	if (im::input_wait_timer < 0)
	{
		im::input_wait_timer = -1.0f;
	}
	else
	{
		im::input_wait_timer -= dt;
	}
}

bool im::press_submit()
{
	if (im::can_press_button() && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
		|| (im::gamepad_connected && sf::Joystick::isButtonPressed(0, im::gamepad_a))))
	{
		im::reset_input_timer();
		return true;
	}

	return false;
}

bool im::press_back()
{
	if (im::can_press_button() && (im::gamepad_connected
		&& sf::Joystick::isButtonPressed(0, im::gamepad_b)))
	{
		im::reset_input_timer();
		return true;
	}

	return false;
}

bool im::press_menu()
{
	if (im::can_press_button() && (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
		|| (im::gamepad_connected && sf::Joystick::isButtonPressed(0, im::gamepad_start))))
	{
		im::reset_input_timer();
		return true;
	}

	return false;
}

bool im::press_up()
{
	if (im::can_press_button() && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		|| (im::gamepad_connected && dpad_y > dpad_dead)))
	{
		im::reset_input_timer();
		return true;
	}

	return false;
}

bool im::press_down()
{
	if (im::can_press_button() && (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		|| (im::gamepad_connected && dpad_y < -dpad_dead)))
	{
		im::reset_input_timer();
		return true;
	}

	return false;
}

bool im::press_left()
{
	if (im::can_press_button() && (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		|| (im::gamepad_connected && dpad_x < -dpad_dead)))
	{
		im::reset_input_timer();
		return true;
	}

	return false;
}

bool im::press_right()
{
	if (im::can_press_button() && (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		|| (im::gamepad_connected && dpad_x > dpad_dead)))
	{
		im::reset_input_timer();
		return true;
	}

	return false;
}

bool im::gamepad_connected()
{
	return sf::Joystick::isConnected(0);
}

bool im::can_press_button()
{
	return im::input_wait_timer < 0;
}

void im::reset_input_timer()
{
	im::input_wait_timer = im::wait_between_input;
}

// Used for key bindings
void im::assign_submit(sf::Keyboard::Key key)
{
	im::submit = key;
}

void im::assign_up(sf::Keyboard::Key key)
{
	im::up = key;
}

void im::assign_down(sf::Keyboard::Key key)
{
	im::down = key;
}

void im::assign_left(sf::Keyboard::Key key)
{
	im::left = key;
}

void im::assign_right(sf::Keyboard::Key key)
{
	im::right = key;
}

void im::reset_key_binds()
{
	im::submit = sf::Keyboard::Space;
	im::up = sf::Keyboard::Up;
	im::down = sf::Keyboard::Down;
	im::left = sf::Keyboard::Left;
	im::right = sf::Keyboard::Right;
}