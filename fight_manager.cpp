#include "fight_manager.hpp"

bool FightManager::_player_consumed_item = false;

void FightManager::update(const float& dt)
{

}

void FightManager::set_player_consumed_item(bool consumed)
{
	FightManager::_player_consumed_item = consumed;
}

bool FightManager::get_player_consumed_item()
{
	return FightManager::_player_consumed_item;
}