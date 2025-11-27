#pragma once
#include <memory>

class FightManager
{
public:
	static void update(const float& dt);
	static void set_player_consumed_item(bool consumed);
	static bool get_player_consumed_item();

private:
	static bool _player_consumed_item;
};