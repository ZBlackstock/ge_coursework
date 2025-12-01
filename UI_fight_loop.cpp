#include "UI_fight_loop.hpp"

using fli = FightLoopIndicator;

std::shared_ptr<sf::Vector2f> fli::_pos = std::make_shared<sf::Vector2f>();

void fli::init()
{
	*_pos = sf::Vector2f{ GameSystem::screen_mid.x, 20 };

	int ic = 0;
	while (ic < 5)
	{
		RenderMan::create_sprite("fightstate_" + std::to_string(ic) + ".png", { 10000,10000 }, 4);
		ic++;
	}
}

void fli::set_fight_loop_state(int state)
{
	int ic = 0;
	while (ic < 5)
	{
		RenderMan::set_sprite_pos("fightstate_" + std::to_string(ic) + ".png", { 10000,10000 });
		ic++;
	}
	RenderMan::set_sprite_pos("fightstate_" + std::to_string(state) + ".png", *fli::_pos);
}