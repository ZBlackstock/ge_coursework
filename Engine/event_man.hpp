#pragma once
#include<memory>
#include"UI_button.hpp"


class EventManager
{
public:
	static std::shared_ptr<Button>  get_current_button();
	static void set_current_button(std::shared_ptr<Button>  button);
	static void update(const float& dt);

private:
	static std::shared_ptr<Button> _currentButton;
	static float wait_between_input;
	static float input_wait_timer;
	static void button_navigate_detect();
};