#include "fight_manager.hpp"

using fli = FightLoopIndicator;
using fm = FightManager;
using h = Healthbar;

bool FightManager::_player_consumed_item = false;
bool FightManager::_player_attacked = false;
bool FightManager::_player_defended = false;
std::shared_ptr<Healthbar> fm::_player_healthbar = std::shared_ptr<Healthbar>();
std::shared_ptr<Healthbar> fm::_enemy_healthbar = std::shared_ptr<Healthbar>();

void FightManager::init()
{
	fli::init();
	fli::set_fight_loop_state(0);
	_player_healthbar = std::make_shared<Healthbar>(sf::Vector2f{ 500,20 }, sf::Vector2f{ 900,900 }, 100, sf::Color::Green);
	_enemy_healthbar = std::make_shared <Healthbar>(sf::Vector2f{ 500,20 }, sf::Vector2f{ 1440,600 }, 100, sf::Color::Red);
	// ^^ Just size, position, max health value, colour
}

void FightManager::update(const float& dt)
{
	// Player consumed item, move to player attack
	if (get_player_consumed_item())
	{
		//Make consumable invisible
		ItemManager::visible(ItemManager::player_consumables, false);
		ItemManager::visible(ItemManager::player_attacks, true);

		EventManager::clear_current_button();
		EventManager::set_current_button(ItemManager::player_attacks[0]->button);

		//Move to attack stage
		fli::set_fight_loop_state(1);
		set_player_consumed_item(false);
	}

	// Player attacked, move to player defend
	if (get_player_attacked())
	{
		//Make attacks invisible
		ItemManager::visible(ItemManager::player_attacks, false);
		ItemManager::visible(ItemManager::player_defends, true);

		EventManager::clear_current_button();
		EventManager::set_current_button(ItemManager::player_defends[0]->button);

		//Move to attack stage
		fli::set_fight_loop_state(2);
		set_player_attacked(false);
	}

	// Player defended, move to enemy turn
	if (get_player_defended())
	{
		//Make attacks invisible
		ItemManager::visible(ItemManager::player_defends, false);

		EventManager::clear_current_button();

		//Move to attack stage
		fli::set_fight_loop_state(3);
		set_player_defended(false);
	}
}

void FightManager::set_player_consumed_item(bool consumed)
{
	FightManager::_player_consumed_item = consumed;
}

bool FightManager::get_player_consumed_item()
{
	return FightManager::_player_consumed_item;
}

void FightManager::set_player_attacked(bool attacked)
{
	FightManager::_player_attacked = attacked;
}

bool FightManager::get_player_attacked()
{
	return FightManager::_player_attacked;
}

void FightManager::set_player_defended(bool defended)
{
	FightManager::_player_defended = defended;
}

bool FightManager::get_player_defended()
{
	return FightManager::_player_defended;
}