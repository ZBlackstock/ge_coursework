#pragma once
#include<memory>
#include"UI_button.hpp"


class EventManager
{
public:
	static std::shared_ptr<Button>  get_current_button();
	static void set_current_button(std::shared_ptr<Button>  button);
	static void clear_current_button();
	static void update(const float& dt);
	//@brief returns if input will be registered
	static bool can_press_button();
	//@brief sets input timer to wait_between_inputs
	static void reset_input_timer();

private:
	static std::shared_ptr<Button> _currentButton;
	static float wait_between_input;
	static float input_wait_timer;
	static void button_navigate_detect();
};