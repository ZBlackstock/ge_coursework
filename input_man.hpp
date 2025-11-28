#pragma once
#include <SFML/Graphics.hpp>
#include "WinSock2.h"
#include "Windows.h"
#include "Xinput.h"

class InputManager
{
public:

	static void Update(const float& dt);
	static const int gamepad_a; // Submit
	static const int gamepad_b; // Back
	static const int gamepad_start; // Menu
	static int lstick_x;
	static int lstick_y;
	static float dpad_x;
	static float dpad_y;
	static const float dpad_dead;

	static bool press_submit(); // enter, space, a
	static bool press_back(); // b
	static bool press_menu(); // start, esc
	static bool press_up();
	static bool press_down();
	static bool press_left();
	static bool press_right();

	//@brief returns if input will be registered
	static bool can_press_button();
	//@brief sets input timer to wait_between_inputs
	static void reset_input_timer();

	static sf::Keyboard::Key submit;
	static sf::Keyboard::Key up;
	static sf::Keyboard::Key down;
	static sf::Keyboard::Key left;
	static sf::Keyboard::Key right;

	static void assign_submit(sf::Keyboard::Key key);
	static void assign_up(sf::Keyboard::Key key);
	static void assign_down(sf::Keyboard::Key key);
	static void assign_left(sf::Keyboard::Key key);
	static void assign_right(sf::Keyboard::Key key);
	static void reset_key_binds();
	static std::string key_to_string(sf::Keyboard::Key key);
	static bool is_any_key_pressed();
	static sf::Keyboard::Key any_key_pressed();

private:
	static bool a_pressed;
	static bool b_pressed;
	static bool start_pressed;
	static bool gamepad_connected();
	static float wait_between_input;
	static float input_wait_timer;
};