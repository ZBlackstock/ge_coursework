#include "item_man.hpp"
#include <iostream>
#include "console.hpp"
#include <cstdlib>
#include "fight_manager.hpp"
#include "game_system.hpp"
#include "message_box.hpp"
#include "UI_fight_loop.hpp"

using cns = Item;
using cman = ItemManager;
using m = MsgBox;
using fli = FightLoopIndicator;

std::vector<std::shared_ptr<Item>> cman::all_consumables;
std::vector<std::shared_ptr<Item>> cman::player_consumables;
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

	// ____________________Fire Damage_____________________
	std::shared_ptr<cns_FireBomb> firebomb = std::make_shared<cns_FireBomb>
		("cns_firebomb", sf::Vector2f{ 10000,10000 }, 50);

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

	// ____________________Rage_____________________
	std::shared_ptr<cns_Rage> rage = std::make_shared<cns_Rage>
		("cns_rage", sf::Vector2f{ 10000,10000 });

	// ____________________QuickEye_____________________
	std::shared_ptr<cns_QuickEye> quick_eye = std::make_shared<cns_QuickEye>
		("cns_quick_eye", sf::Vector2f{ 10000,10000 });

	// ____________________Oil_____________________
	std::shared_ptr<cns_Oil> oil = std::make_shared<cns_Oil>
		("cns_oil", sf::Vector2f{ 10000,10000 });

	healing_potion0->button->set_consumable(healing_potion0);
	healing_potion1->button->set_consumable(healing_potion1);
	healing_potion2->button->set_consumable(healing_potion2);
	fire_resistance->button->set_consumable(fire_resistance);
	sharp_resistance->button->set_consumable(sharp_resistance);
	firebomb->button->set_consumable(firebomb);
	thorns->button->set_consumable(thorns);
	illusion->button->set_consumable(illusion);
	whetstone->button->set_consumable(whetstone);
	fire_blessing->button->set_consumable(fire_blessing);
	rage->button->set_consumable(rage);
	quick_eye->button->set_consumable(quick_eye);
	oil->button->set_consumable(oil);

	cman::all_consumables.push_back(healing_potion0);
	cman::all_consumables.push_back(healing_potion1);
	cman::all_consumables.push_back(healing_potion2);
	cman::all_consumables.push_back(fire_resistance);
	cman::all_consumables.push_back(sharp_resistance);
	cman::all_consumables.push_back(firebomb);
	cman::all_consumables.push_back(thorns);
	cman::all_consumables.push_back(illusion);
	cman::all_consumables.push_back(whetstone);
	cman::all_consumables.push_back(fire_blessing);
	cman::all_consumables.push_back(rage);
	cman::all_consumables.push_back(quick_eye);
	cman::all_consumables.push_back(oil);

	sf::Vector2f consumable_pos = { 100, 100 };
	for (int i = 0; i < cman::num_player_consumables; ++i)
	{
		srand(time(0));
		int random = rand() % cman::all_consumables.size();
		cman::all_consumables[random]->button->set_pos(consumable_pos);
		cman::player_consumables.push_back(cman::all_consumables[random]);
		cman::all_consumables[random]->set_display_texts();
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

void cman::visible(bool visible)
{
	for (int i = 0; i < cman::num_player_consumables; ++i)
	{
		cman::player_consumables[i]->button->set_all_sprites_pos(visible ? cman::player_consumables[i]->get_pos() : sf::Vector2f{ 10000, 10000 });
	}
}

//____________________Consumables_________________________________________________________________________
cns::Item(std::string name, sf::Vector2f pos)
{
	cns::_name = name;
	cns::_pos = pos;
	cns::button = std::make_shared<Button_Consumable>(name, pos, 3);

	_txt_display_name->setFont(GameSystem::font_bold);
	_txt_display_name->setCharacterSize(50);
	_txt_display_name->setColor(sf::Color::White);
	_txt_display_name->setPosition(200, 80);

	_txt_display_description->setFont(GameSystem::font);
	_txt_display_description->setCharacterSize(30);
	_txt_display_description->setColor(sf::Color::White);
	_txt_display_description->setPosition(200, 150);

	RenderMan::createDrawable(_txt_display_name, 3);
	RenderMan::createDrawable(_txt_display_description, 3);
}
void cns::on_use()
{
	FightManager::set_player_consumed_item(true);
	cns::button->disable();
	fli::set_fight_loop_state(1);
	Console::print("on_use()");
}

sf::Vector2f cns::get_pos()
{
	return _pos;
}

std::string cns::get_name()
{
	return cns::_name;
}

void cns::display_description(bool display)
{
	Console::print("cns::display_description() " + std::to_string(display));
	Console::print(_display_name);
	Console::print(_display_description);
	_txt_display_name->setString(display ? _display_name : "");
	_txt_display_description->setString(display ? _display_description : "");

	_txt_display_name->setOrigin(0, _txt_display_name->getLocalBounds().height / 2);
	_txt_display_description->setOrigin(0, 0);
}
void cns::set_display_texts() {}

//____________________________

// Healing Potion
void cns_HealingPotion::on_use()
{
	cns::on_use();
	m::set_text("Health Potion Used. Regained " + std::to_string(cns_HealingPotion::_heal_amount) + " health!");
}
void cns_HealingPotion::set_display_texts()
{
	Console::print("hello");
	_display_name = "Healing Potion";
	_display_description =
		"A common concoction found in a variety of sizes. \n \nGrants " + std::to_string(_heal_amount) + " health";
}

// Fire Resistance
void cns_FireResistance::on_use()
{
	cns::on_use();
	m::set_text("Fire resistance gained! The next fire attack that lands will deal less damage");
}
void cns_FireResistance::set_display_texts()
{
	_display_name = "Fire Resistance";
	_display_description = "Provides resistance to fire \ndamage for a limited time";
}

// Sharp Resistance
void cns_SharpResistance::on_use()
{
	cns::on_use();
	m::set_text("Sharp resistance gained! The next fire attack that lands will deal less damage");
}
void cns_SharpResistance::set_display_texts()
{
	_display_name = "Sharp Resistance";
	_display_description = "Provides resistance to sharp \ndamage for a limited time";
}

// Blunt resistance
void cns_FireBomb::on_use()
{
	cns::on_use();
	m::set_text("Fire Bomb thrown at enemy!");
}
void cns_FireBomb::set_display_texts()
{
	_display_name = "Fire Bomb";
	_display_description = "Throw at foes to \ninflict fire damage";
}

// Thorns
void cns_Thorns::on_use()
{
	cns::on_use();
	m::set_text("Thorns used!");
}
void cns_Thorns::set_display_texts()
{
	_display_name = "Thorns";
	_display_description = "Your foes next landing \nattack will hurt them too";
}

// Illusion
void cns_Illusion::on_use()
{
	cns::on_use();
	m::set_text("Illusion cast!");
}
void cns_Illusion::set_display_texts()
{
	_display_name = "Illusion";
	_display_description =
		"Casts an illusory self, \nconfusing your opponent and \navoiding damage from \ntheir next attack";
}

// Fire buff
void cns_FireBlessing::on_use()
{
	cns::on_use();
	m::set_text("Fire blessing recieved!");
}
void cns_FireBlessing::set_display_texts()
{
	_display_name = "Fire Blessing";
	_display_description =
		"Temporarily wraps your blade \nin flames. \n\nYour next attack will also \ndeal Fire damage";
}

// Sharp buff
void cns_Whetstone::on_use()
{
	cns::on_use();
	m::set_text("Blade sharpened by Whetstone!");
}
void cns_Whetstone::set_display_texts()
{
	_display_name = "Whetstone";
	_display_description = "Sharpens blade, allowing for \nadditional sharp damage on your \nnext attack";
}

// Rage
void cns_Rage::on_use()
{
	cns::on_use();
	m::set_text("Enraged!");
}
void cns_Rage::set_display_texts()
{
	_display_name = "Rage";
	_display_description =
		"Unleashes your fury. \n\nYour next attack will deal additional \ndamage, but your unstable anger reduces \nlikelihood of a connection";
}

// Quickeye
void cns_QuickEye::on_use()
{
	cns::on_use();
	m::set_text("Utilising Quick Eye!");
}
void cns_QuickEye::set_display_texts()
{
	_display_name = "Quick Eye";
	_display_description = "Momentarily improve awareness.\n\nTemporarily increases likelihood \nof parry success.";
}

// Oil
void cns_Oil::on_use()
{
	cns::on_use();
	m::set_text("Oil thrown!");
}
void cns_Oil::set_display_texts()
{
	_display_name = "Oil";
	_display_description = "Coats foe in oil.\n\nYour foes next fire \nattack will ignite them.";
}
