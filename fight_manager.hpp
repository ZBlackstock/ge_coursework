#pragma once
#include <memory>
#include "message_box.hpp"
#include "UI_fight_loop.hpp"
#include "item_man.hpp"
#include "event_man.hpp"
#include "healthbar.hpp"

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

private:
	static bool _player_consumed_item;
	static bool _player_attacked;
	static bool _player_defended;
	static std::shared_ptr<Healthbar> _player_healthbar;
	static std::shared_ptr<Healthbar> _enemy_healthbar;
};