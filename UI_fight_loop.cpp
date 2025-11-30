#include "UI_fight_loop.hpp"

using fli = FightLoopIndicator;

std::shared_ptr<sf::Vector2f> fli::_pos = std::make_shared<sf::Vector2f>();

void fli::init()
{
	*_pos = sf::Vector2f{ GameSystem::screen_mid.x, 20 };
}

void fli::set_fight_loop_state(int state)
{
	RenderMan::create_sprite("fightstate_" + state, *fli::_pos, 4);
}