#pragma once
#include <SFML/Graphics.hpp>
#include "WinSock2.h"
#include "Windows.h"
#include "Xinput.h"

class InputManager
{
public:

	void Update();
	const int gamepad_a = 0; // Submit
	const int gamepad_b = 1; // Back
	const int gamepad_start = 7; // Menu
	const int lstick_x = 0;
	const int lstick_y = 1;
	const int dpad_x = 0;
	const int dpad_y = 1;

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

};