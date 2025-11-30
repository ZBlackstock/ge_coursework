#pragma once
#include "Engine\RenderMan.h"
#include "Engine\game_system.hpp"

class FightLoopIndicator
{
public:
	//0 - consume item, 1 - attack, 2 - defend, 
	// 3 - enemy consume item, 4 - enemy attack, 5 - enemy defend
	static void set_fight_loop_state(int state);
	static void init();

private:
	static std::shared_ptr<sf::Vector2f> _pos;
};