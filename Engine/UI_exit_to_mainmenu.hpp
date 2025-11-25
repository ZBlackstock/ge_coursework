#pragma once
#include <memory>
#include "RenderMan.h"
#include <SFML/Graphics.hpp>
#include "UI_button.hpp"


// Zach
// Manages popup that appears when you press Esc
class ExitToMainMenu
{
public:
	static void init();
	static void set_active(bool active);
	static std::shared_ptr<Button_LoadScene> yes;
	static std::shared_ptr<Button> no;
};
