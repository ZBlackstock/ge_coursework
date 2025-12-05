#include "fight_manager.hpp"
#include "BasicEntityStats.h"
#include "AI/AI_cmps.h"
#include "console.hpp"

using fli = FightLoopIndicator;
using fm = FightManager;
using h = Healthbar;

bool FightManager::_player_consumed_item = false;
bool FightManager::_player_attacked = false;
bool FightManager::_player_defended = false;
std::shared_ptr<Healthbar> fm::_player_healthbar =nullptr;
std::shared_ptr<Healthbar> fm::_enemy_healthbar = nullptr;
bool FightManager::player_Block = false;



bool FightManager::_enemy_consumed_item = false;
bool FightManager::_enemy_attacked = false;
bool FightManager::_enemy_defended = false;
bool FightManager::enemy_Block = false;


void FightManager::init()
{
	fli::init();
	fli::set_fight_loop_state(0);
	_player_healthbar = std::make_shared<Healthbar>(sf::Vector2f{ 500,20 }, sf::Vector2f{ 900,900 }, 100, sf::Color::Green);
	_enemy_healthbar = std::make_shared <Healthbar>(sf::Vector2f{ 500,20 }, sf::Vector2f{ 1440,600 }, 100, sf::Color::Red);
	ItemManager::visible(ItemManager::player_consumables, true);
	// ^^ Just size, position, max health value, colour
}

void FightManager::update(const float& dt)
{
	if (_player_healthbar == nullptr)
	{
		_player_healthbar = std::make_shared<Healthbar>(sf::Vector2f{ 500,20 }, sf::Vector2f{ 900,900 },
			ItemManager::get_player()->get_compatible_components<BasicEntityStats>()[0]->get_max_health(), sf::Color::Green);
		_enemy_healthbar = std::make_shared <Healthbar>(sf::Vector2f{ 500,20 }, sf::Vector2f{ 1440,600 },
			ItemManager::get_enemy()->get_compatible_components<BasicEntityStats>()[0]->get_max_health(), sf::Color::Red);
	}

	

	std::vector<std::shared_ptr<AIComponent>> entityComp = ItemManager::get_enemy()->get_compatible_components<AIComponent>();

	// PLAYER CONSUME
	if (get_enemy_defended())
	{
		RenderMan::RenderWindow(); // Otherwise sf::sleep would pause before rendering
		sf::sleep(sf::seconds(1.f));

		ItemManager::visible(ItemManager::player_consumables, true);
		EventManager::set_current_button(ItemManager::player_consumables[0]->button);

		//Move to attack stage
		fli::set_fight_loop_state(0);
		set_enemy_defended(false);
		Console::print("PLAYER CONSUME");

	}

	// PLAYER ATTACK
	if (get_player_consumed_item())
	{
		//Make consumable invisible
		ItemManager::visible(ItemManager::player_consumables, false);
		ItemManager::visible(ItemManager::player_attacks, true);

		EventManager::set_current_button(ItemManager::player_attacks[0]->button);

		//Move to attack stage
		fli::set_fight_loop_state(1);
		set_player_consumed_item(false);
		Console::print("PLAYER ATTACK");

	}

	_enemy_healthbar->set_healthbar_value(ItemManager::get_enemy()->get_compatible_components<BasicEntityStats>()[0]->current_health);

	// PLAYER DEFEND
	if (get_player_attacked())
	{
		//Make attacks invisible
		ItemManager::visible(ItemManager::player_attacks, false);
		ItemManager::visible(ItemManager::player_defends, true);

		EventManager::set_current_button(ItemManager::player_defends[0]->button);

		//Move to defend stage
		fli::set_fight_loop_state(2);
		set_player_attacked(false);
		Console::print("PLAYER DEFEND");

	}

	// ENEMY CONSUME
	if (get_player_defended())
	{
		//Make attacks invisible
		ItemManager::visible(ItemManager::player_defends, false);

		EventManager::clear_current_button();

		//Move to attack stage
		fli::set_fight_loop_state(3);

		RenderMan::RenderWindow(); // Otherwise sf::sleep would pause before rendering
		sf::sleep(sf::seconds(1.f));

		entityComp[0]->set_State("Item");
		entityComp[0]->update(dt);

		//Move to attack stage
		set_enemy_consumed_item(true);
		set_player_defended(false);
		Console::print("ENEMY CONSUME");

	}

	// ENEMY ATTACK
	if (get_enemy_consumed_item())
	{
		ItemManager::visible(ItemManager::player_defends, false);

		entityComp[0]->set_State("Attack");
		entityComp[0]->update(dt);

		//Move to defend stage
	//	fli::set_fight_loop_state(4);
		RenderMan::RenderWindow();
		sf::sleep(sf::seconds(2.f));
		
		set_enemy_consumed_item(false);
		Console::print("ENEMY ATTACK");
		ItemManager::visible(ItemManager::player_defends, false);

	}
	
	_player_healthbar->set_healthbar_value(ItemManager::get_player()->get_compatible_components<BasicEntityStats>()[0]->current_health);

	// ENEMY DEFEND
	if (get_enemy_attacked())
	{
		RenderMan::RenderWindowClear();
		fli::set_fight_loop_state(5);
		
		RenderMan::RenderWindow(); // Otherwise sf::sleep would pause before rendering
		sf::sleep(sf::seconds(2.f));

		entityComp[0]->set_State("Block");
		entityComp[0]->update(dt);

		set_enemy_attacked(false);
		Console::print("ENEMY DEFEND");
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


//enemy fight stuff
void FightManager::set_enemy_consumed_item(bool consumed)
{
	FightManager::_enemy_consumed_item = consumed;
}

bool FightManager::get_enemy_consumed_item()
{
	return FightManager::_enemy_consumed_item;
}

void FightManager::set_enemy_attacked(bool attacked)
{
	FightManager::_enemy_attacked = attacked;
}

bool FightManager::get_enemy_attacked()
{
	return FightManager::_enemy_attacked;
}

void FightManager::set_enemy_defended(bool defended)
{
	FightManager::_enemy_defended = defended;
}

bool FightManager::get_enemy_defended()
{
	return FightManager::_enemy_defended;
}


