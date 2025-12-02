#pragma once
#include <memory>
#include "Engine/RenderMan.h"
#include <SFML/Graphics.hpp>
#include "UI_button.hpp"


// Zach
// Manages popup that appears when you press Esc
class ExitToMainMenu
{
public:
	ExitToMainMenu() = delete;
	static void init();
	static std::shared_ptr<Button> get_button_before_open();
	static void set_active(bool active);
	static bool get_active();
	static std::shared_ptr<Button_LoadScene> yes;
	static std::shared_ptr<Button> no;

private:
	static std::shared_ptr<bool> _active;
	static std::shared_ptr<Button> _button_before_open;
};
