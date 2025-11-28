#include "input_man.hpp"
#include "Engine/RenderMan.h"
#include <iostream>
#include "console.hpp"

using im = InputManager;
const int im::gamepad_a = 0; // Submit
const int im::gamepad_b = 1; // Back
const int im::gamepad_start = 7; // Menu
int im::lstick_x = 0;
int im::lstick_y = 1;
float im::dpad_x = 0;
float im::dpad_y = 0;
const float im::dpad_dead = 0.1f;
float im::wait_between_input = 0.15f; // To stop holding down keys spamming buttons
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
	Console::print("im::assign_submit: " + key);
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

static bool is_any_key_pressed()
{

}
static sf::Keyboard::Key any_key_pressed()
{

}

std::string im::key_to_string(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::A: return "A";
	case sf::Keyboard::B: return "B";
	case sf::Keyboard::C: return "C";
	case sf::Keyboard::D: return "D";
	case sf::Keyboard::E: return "E";
	case sf::Keyboard::F: return "F";
	case sf::Keyboard::G: return "G";
	case sf::Keyboard::H: return "H";
	case sf::Keyboard::I: return "I";
	case sf::Keyboard::J: return "J";
	case sf::Keyboard::K: return "K";
	case sf::Keyboard::L: return "L";
	case sf::Keyboard::M: return "M";
	case sf::Keyboard::N: return "N";
	case sf::Keyboard::O: return "O";
	case sf::Keyboard::P: return "P";
	case sf::Keyboard::Q: return "Q";
	case sf::Keyboard::R: return "R";
	case sf::Keyboard::S: return "S";
	case sf::Keyboard::T: return "T";
	case sf::Keyboard::U: return "U";
	case sf::Keyboard::V: return "V";
	case sf::Keyboard::W: return "W";
	case sf::Keyboard::X: return "X";
	case sf::Keyboard::Y: return "Y";
	case sf::Keyboard::Z: return "Z";
	case sf::Keyboard::Num0: return "0";
	case sf::Keyboard::Num1: return "1";
	case sf::Keyboard::Num2: return "2";
	case sf::Keyboard::Num3: return "3";
	case sf::Keyboard::Num4: return "4";
	case sf::Keyboard::Num5: return "5";
	case sf::Keyboard::Num6: return "6";
	case sf::Keyboard::Num7: return "7";
	case sf::Keyboard::Num8: return "8";
	case sf::Keyboard::Num9: return "9";
	case sf::Keyboard::Space: return "Space";
	case sf::Keyboard::Enter: return "Enter";
	case sf::Keyboard::Escape: return "Escape";
	case sf::Keyboard::Backspace: return "Backspace";
	case sf::Keyboard::Tab: return "Tab";
	case sf::Keyboard::LShift: return "Left Shift";
	case sf::Keyboard::RShift: return "Right Shift";
	case sf::Keyboard::LControl: return "Left Ctrl";
	case sf::Keyboard::RControl: return "Right Ctrl";
	case sf::Keyboard::Up: return "Up";
	case sf::Keyboard::Down: return "Down";
	case sf::Keyboard::Left: return "Left";
	case sf::Keyboard::Right: return "Right";

	default: return "Unknown";
	}
}