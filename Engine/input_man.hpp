#pragma once
#include <SFML/Graphics.hpp>
#include "WinSock2.h"
#include "Windows.h"
#include "Xinput.h"

class InputManager
{
public:

	static void Update();
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

private:
	static bool a_pressed;
	static bool b_pressed;
	static bool start_pressed;
	static bool gamepad_connected();
};