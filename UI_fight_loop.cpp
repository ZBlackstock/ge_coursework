#include "UI_fight_loop.hpp"

using fli = FightLoopIndicator;

std::shared_ptr<sf::Vector2f> fli::_pos = std::make_shared<sf::Vector2f>();

void fli::init()
{
	*_pos = sf::Vector2f{ GameSystem::screen_mid.x, 20 };

	int i = 0;
	while (i < 5)
	{
		RenderMan::create_sprite("fightstate_" + std::to_string(i) + ".png", { 10000,10000 }, 4);
		i++;
	}
}

void fli::set_fight_loop_state(int state)
{
	int i = 0;
	while (i < 5)
	{
		RenderMan::set_sprite_pos("fightstate_" + std::to_string(i) + ".png", { 10000,10000 });
		i++;
	}
	RenderMan::set_sprite_pos("fightstate_" + std::to_string(state) + ".png", *fli::_pos);
}