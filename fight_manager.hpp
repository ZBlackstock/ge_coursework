#pragma once
#include <memory>
#include "message_box.hpp"
#include "UI_fight_loop.hpp"
#include "item_man.hpp"
#include "event_man.hpp"
#include "healthbar.hpp"
#include "Engine/ecm.hpp"	

class FightManager
{
public:
	static void init();
	static void update(const float& dt);


	static void set_player_consumed_item(bool consumed);
	static bool get_player_consumed_item();

	static void set_player_attacked(bool attacked);
	static bool get_player_attacked();

	static void set_player_defended(bool defended);
	static bool get_player_defended();


	static void set_enemy_consumed_item(bool consumed);
	static bool get_enemy_consumed_item();

	static void set_enemy_attacked(bool attacked);
	static bool get_enemy_attacked();

	static void set_enemy_defended(bool defended);
	static bool get_enemy_defended();


	static std::shared_ptr<Entity> player;
	static std::shared_ptr<Entity> enemy;

	static bool player_Block;
	static bool enemy_Block; 

	//static const std::shared_ptr<Entity>* player;
	//static const std::shared_ptr<Entity>* enemy;

private:
	static bool _player_consumed_item;
	static bool _player_attacked;
	static bool _player_defended;
	static bool _enemy_consumed_item;
	static bool _enemy_attacked;
	static bool _enemy_defended;

	static std::shared_ptr<Healthbar> _player_healthbar;
	static std::shared_ptr<Healthbar> _enemy_healthbar;
};