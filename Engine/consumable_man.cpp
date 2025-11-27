#include "consumable_man.hpp"

using cns = Consumable;
using cman = ConsumableManager;

cns::Consumable(std::string name, sf::Vector2f pos)
{
	cns::_name = name;
	cns::_pos = pos;
	cns::button = std::make_shared<Button>(name, pos, 3);
}


//____________________Consumables_________________________________________________________________________

// Healing Potion
cns_HealingPotion::cns_HealingPotion(std::string name, sf::Vector2f pos, int heal_amount) : Consumable(name, pos)
{
	cns_HealingPotion::_heal_amount = heal_amount;
}
void cns_HealingPotion::on_use()
{

}

// Fire Resistance
cns_FireResistance::cns_FireResistance(std::string name, sf::Vector2f pos, int resistance) : Consumable(name, pos)
{
	cns_FireResistance::_resistance = resistance;
}
void cns_FireResistance::on_use()
{

}

// Sharp Resistance
cns_SharpResistance::cns_SharpResistance(std::string name, sf::Vector2f pos, int resistance) : Consumable(name, pos)
{
	cns_SharpResistance::_resistance = resistance;
}
void cns_SharpResistance::on_use()
{

}

// Blunt resistance
cns_BluntResistance::cns_BluntResistance(std::string name, sf::Vector2f pos, int resistance) : Consumable(name, pos)
{
	cns_BluntResistance::_resistance = resistance;
}
void cns_BluntResistance::on_use()
{

}

// Insight
cns_Insight::cns_Insight(std::string name, sf::Vector2f pos) : Consumable(name, pos) {}
void cns_Insight::on_use()
{

}

// Thorns
cns_Thorns::cns_Thorns(std::string name, sf::Vector2f pos) : Consumable(name, pos) {}
void cns_Thorns::on_use()
{

}

// Illusion
cns_Illusion::cns_Illusion(std::string name, sf::Vector2f pos) : Consumable(name, pos) {}
void cns_Illusion::on_use()
{

}

// Fire buff
cns_FireBlessing::cns_FireBlessing(std::string name, sf::Vector2f pos) : Consumable(name, pos) {}
void cns_FireBlessing::on_use()
{

}

// Sharp buff
cns_Whetstone::cns_Whetstone(std::string name, sf::Vector2f pos) : Consumable(name, pos) {}
void cns_Whetstone::on_use()
{

}

// Next player attack will deal additional Blunt damage
cns_StrengthBlessing::cns_StrengthBlessing(std::string name, sf::Vector2f pos) : Consumable(name, pos) {}
void cns_StrengthBlessing::on_use()
{

}

// Rage
cns_Rage::cns_Rage(std::string name, sf::Vector2f pos) : Consumable(name, pos) {}
void cns_Rage::on_use()
{

}

// Quickeye
cns_QuickEye::cns_QuickEye(std::string name, sf::Vector2f pos) : Consumable(name, pos) {}
void cns_QuickEye::on_use()
{

}

// Oil
cns_Oil::cns_Oil(std::string name, sf::Vector2f pos) : Consumable(name, pos) {}
void cns_Oil::on_use()
{

}