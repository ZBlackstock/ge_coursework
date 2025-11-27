#include "consumable_man.hpp"
#include <iostream>
#include "console.hpp"
#include <cstdlib>
#include "fight_manager.hpp"

using cns = Consumable;
using cman = ConsumableManager;


std::vector<std::shared_ptr<Consumable>> cman::all_consumables;
std::vector<std::shared_ptr<Consumable>> cman::player_consumables;
int cman::num_player_consumables = 8;

void cman::init()
{
	Console::print("ConsumableManager Init()");

	// ____________________Small healing potion_____________________
	std::shared_ptr<cns_HealingPotion> healing_potion0 = std::make_shared<cns_HealingPotion>
		("cns_health_potion", sf::Vector2f{ 10000,10000 }, 30);

	// ____________________Medium healing potion_____________________
	std::shared_ptr<cns_HealingPotion> healing_potion1 = std::make_shared<cns_HealingPotion>
		("cns_health_potion1", sf::Vector2f{ 10000,10000 }, 30);

	// ____________________Large healing potion_____________________
	std::shared_ptr<cns_HealingPotion> healing_potion2 = std::make_shared<cns_HealingPotion>
		("cns_health_potion2", sf::Vector2f{ 10000,10000 }, 30);

	// ____________________Fire Resistance_____________________
	std::shared_ptr<cns_FireResistance> fire_resistance = std::make_shared<cns_FireResistance>
		("cns_fire_resistance", sf::Vector2f{ 10000,10000 }, 70);

	// ____________________Sharp Resistance_____________________
	std::shared_ptr<cns_SharpResistance> sharp_resistance = std::make_shared<cns_SharpResistance>
		("cns_sharp_resistance", sf::Vector2f{ 10000,10000 }, 50);

	// ____________________Blunt Resistance_____________________
	std::shared_ptr<cns_BluntResistance> blunt_resistance = std::make_shared<cns_BluntResistance>
		("cns_blunt_resistance", sf::Vector2f{ 10000,10000 }, 50);

	// ____________________Insight_____________________
	std::shared_ptr<cns_Insight> insight = std::make_shared<cns_Insight>
		("cns_insight", sf::Vector2f{ 10000,10000 });

	// ____________________Thorns_____________________
	std::shared_ptr<cns_Thorns> thorns = std::make_shared<cns_Thorns>
		("cns_thorns", sf::Vector2f{ 10000,10000 });

	// ____________________Illusion_____________________
	std::shared_ptr<cns_Illusion> illusion = std::make_shared<cns_Illusion>
		("cns_illusion", sf::Vector2f{ 10000,10000 });

	// ____________________Whetstone_____________________
	std::shared_ptr<cns_Whetstone> whetstone = std::make_shared<cns_Whetstone>
		("cns_whetstone", sf::Vector2f{ 10000,10000 });

	// ____________________Fire Blessing_____________________
	std::shared_ptr<cns_FireBlessing> fire_blessing = std::make_shared<cns_FireBlessing>
		("cns_fire_blessing", sf::Vector2f{ 10000,10000 });

	// ____________________Strength Blessing_____________________
	std::shared_ptr<cns_StrengthBlessing> strength_blessing = std::make_shared<cns_StrengthBlessing>
		("cns_strength_blessing", sf::Vector2f{ 10000,10000 });

	// ____________________Rage_____________________
	std::shared_ptr<cns_Rage> rage = std::make_shared<cns_Rage>
		("cns_rage", sf::Vector2f{ 10000,10000 });

	// ____________________QuickEye_____________________
	std::shared_ptr<cns_QuickEye> quick_eye = std::make_shared<cns_QuickEye>
		("cns_quick_eye", sf::Vector2f{ 10000,10000 });

	// ____________________Oil_____________________
	std::shared_ptr<cns_Oil> oil = std::make_shared<cns_Oil>
		("cns_oil", sf::Vector2f{ 10000,10000 });

	cman::all_consumables.push_back(healing_potion0);
	cman::all_consumables.push_back(healing_potion1);
	cman::all_consumables.push_back(healing_potion2);
	cman::all_consumables.push_back(fire_resistance);
	cman::all_consumables.push_back(sharp_resistance);
	cman::all_consumables.push_back(blunt_resistance);
	cman::all_consumables.push_back(insight);
	cman::all_consumables.push_back(thorns);
	cman::all_consumables.push_back(illusion);
	cman::all_consumables.push_back(whetstone);
	cman::all_consumables.push_back(fire_blessing);
	cman::all_consumables.push_back(strength_blessing);
	cman::all_consumables.push_back(rage);
	cman::all_consumables.push_back(quick_eye);
	cman::all_consumables.push_back(oil);

	sf::Vector2f consumable_pos = { 100, 100 };
	for (int i = 0; i < cman::num_player_consumables; ++i)
	{
		srand(time(0));
		int random = rand() % cman::all_consumables.size();
		cman::all_consumables[random]->set_pos(consumable_pos);
		cman::player_consumables.push_back(cman::all_consumables[random]);
		cman::all_consumables.erase(cman::all_consumables.begin() + random);
		consumable_pos.y += 120;

		if (cman::player_consumables.size() > 1)
		{
			cman::player_consumables[i]->button->set_above(cman::player_consumables[i - 1]->button);
			cman::player_consumables[i - 1]->button->set_below(cman::player_consumables[i]->button);

			if (i == cman::num_player_consumables - 1)
			{
				cman::player_consumables[i]->button->set_below(cman::player_consumables[0]->button);
				cman::player_consumables[0]->button->set_above(cman::player_consumables[i]->button);
			}
		}
	}
}

//____________________Consumables_________________________________________________________________________
cns::Consumable(std::string name, sf::Vector2f pos)
{
	cns::_name = name;
	cns::_pos = pos;
	cns::button = std::make_shared<Button>(name, pos, 3);
}
void cns::on_use() 
{
	FightManager::set_player_consumed_item(true);
}
void cns::set_pos(sf::Vector2f pos)
{
	cns::button->set_pos(pos);
}

//____________________________

// Need to wait for louis to do player entity so I can modify values via these

// Healing Potion
void cns_HealingPotion::on_use()
{

}

// Fire Resistance
void cns_FireResistance::on_use()
{

}

// Sharp Resistance
void cns_SharpResistance::on_use()
{

}

// Blunt resistance
void cns_BluntResistance::on_use()
{

}

// Insight
void cns_Insight::on_use()
{

}

// Thorns
void cns_Thorns::on_use()
{

}

// Illusion
void cns_Illusion::on_use()
{

}

// Fire buff
void cns_FireBlessing::on_use()
{

}

// Sharp buff
void cns_Whetstone::on_use()
{

}

// Strength buff
void cns_StrengthBlessing::on_use()
{

}

// Rage
void cns_Rage::on_use()
{

}

// Quickeye
void cns_QuickEye::on_use()
{

}

// Oil
void cns_Oil::on_use()
{

}