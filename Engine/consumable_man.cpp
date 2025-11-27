#include "consumable_man.hpp"

using cns = Consumable;
using cman = ConsumableManager;

cns::Consumable(std::string name, sf::Vector2f pos)
{
	cns::_name = name;
	cns::_pos = pos;
	cns::button = std::make_shared<Button>(name,pos,3);
}

