#include "fight_manager.hpp"

using fli = FightLoopIndicator;
using h = Healthbar;

bool FightManager::_player_consumed_item = false;
bool FightManager::_player_attacked = false;
std::shared_ptr<Healthbar> _player_healthbar = std::shared_ptr<Healthbar>();
std::shared_ptr<Healthbar> _enemy_healthbar = std::shared_ptr<Healthbar>();

void FightManager::init()
{
	fli::init();
	fli::set_fight_loop_state(0);
	*_player_healthbar = h::Healthbar(sf::Vector2f{ 200,10 }, sf::Vector2f{ 1000,1000 }, 100);
	*_enemy_healthbar = h::Healthbar(sf::Vector2f{ 200,10 }, sf::Vector2f{ 1500,500 }, 100);
	// ^^ Just size, position, max health value
}

void FightManager::update(const float& dt)
{
	if (get_player_consumed_item())
	{
		//Make consumable invisible
		ConsumableManager::visible(false);
		EventManager::clear_current_button();

		//Move to attack stage
		fli::set_fight_loop_state(1);
		set_player_consumed_item(false);
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