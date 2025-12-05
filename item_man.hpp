#pragma once
#include <memory>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "UI_button.hpp"
#include "BasicEntityStats.h"

// Forward definition
class Item;
class Button_Item;

class ItemManager
{
public:
	static std::vector<std::shared_ptr<Item>> all_consumables;
	static std::vector<std::shared_ptr<Item>> player_consumables;
	static std::vector<std::shared_ptr<Item>> player_attacks;
	static std::vector<std::shared_ptr<Item>> player_defends;
	static void init();
	static void clear();
	static void visible(std::vector<std::shared_ptr<Item>> list, bool visible);
	static int num_player_consumables;

	static bool attack_used(bool is_heavy, std::shared_ptr<Entity> aggresor);

	static void set_player(std::shared_ptr<Entity> entity);
	static void set_enemy(std::shared_ptr<Entity> entity);

	static std::shared_ptr<Entity> get_player();
	static std::shared_ptr<Entity> get_enemy();

protected:
	static std::shared_ptr<Entity> player;
	static std::shared_ptr<Entity> enemy;
};

class Item
{
public:
	Item(std::string name, sf::Vector2f pos);

	std::shared_ptr<Button_Item> button = nullptr;
	virtual void on_use();
	sf::Vector2f get_pos();
	void display_description(bool display);
	virtual void set_display_texts();
	std::string get_name();

protected:
	std::string _name;
	sf::Vector2f _pos;
	std::shared_ptr< sf::Text> _txt_display_name = std::make_shared<sf::Text>();
	std::shared_ptr< sf::Text> _txt_display_description = std::make_shared<sf::Text>();

	std::string _display_name;
	std::string _display_description;
};

class Item_Consumable : public Item
{
public:
	Item_Consumable(std::string name, sf::Vector2f pos) : Item(name, pos) {};
	void on_use() override;
};

class Item_Attack : public Item
{
public:
	Item_Attack(std::string name, sf::Vector2f pos) : Item(name, pos) {};
	void on_use() override;
	int damage = 0;
};

class Item_Defend : public Item
{
public:
	Item_Defend(std::string name, sf::Vector2f pos) : Item(name, pos) {};
	void on_use() override;
};

// ______________CUSTOM CONSUMABLES__________________

// Heal player by amount
class cns_HealingPotion : public Item_Consumable
{
public:
	cns_HealingPotion(std::string name, sf::Vector2f pos, int heal_amount) : Item_Consumable(name, pos), _heal_amount(heal_amount) {}
	void on_use() override;
	void set_display_texts() override;

private:
	int _heal_amount;
};

// Resistant to next fire damage dealt
class cns_FireResistance : public Item_Consumable
{
public:
	cns_FireResistance(std::string name, sf::Vector2f pos, int resistance) : Item_Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;

private:
	int _resistance;
};

// Resistant to next sharp damage dealt
class cns_SharpResistance : public Item_Consumable
{
public:
	cns_SharpResistance(std::string name, sf::Vector2f pos, int resistance) : Item_Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;

private:
	int _resistance;
};

// Resistant to next blunt damage dealt
class cns_FireBomb : public Item_Consumable
{
public:
	cns_FireBomb(std::string name, sf::Vector2f pos, int damage) : Item_Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;

private:
	int _damage;
};

// If enemy's next attack lands, it will deal half of recieved damage to the enemy
class cns_Thorns : public Item_Consumable
{
public:
	cns_Thorns(std::string name, sf::Vector2f pos) : Item_Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// Enemy's next attack double likely to miss
class cns_Illusion : public Item_Consumable
{
public:
	cns_Illusion(std::string name, sf::Vector2f pos) : Item_Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// Next player attack will deal additional fire damage
class cns_FireBlessing : public Item_Consumable
{
public:
	cns_FireBlessing(std::string name, sf::Vector2f pos) : Item_Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// Next player attack will deal additional sharp damage
class cns_Whetstone : public Item_Consumable
{
public:
	cns_Whetstone(std::string name, sf::Vector2f pos) : Item_Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// Next player attack will deal double damage, but is less likely to land
class cns_Rage : public Item_Consumable
{
public:
	cns_Rage(std::string name, sf::Vector2f pos) : Item_Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// Next player parry is more likely to be successful
class cns_QuickEye : public Item_Consumable
{
public:
	cns_QuickEye(std::string name, sf::Vector2f pos) : Item_Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// If enemy performs fire attack, they will take the fire damage
class cns_Oil : public Item_Consumable
{
public:
	cns_Oil(std::string name, sf::Vector2f pos) : Item_Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// ______________CUSTOM ATTACKS__________________

// Light Attack
class atk_Light : public Item_Attack
{
public:
	atk_Light(std::string name, sf::Vector2f pos) : Item_Attack(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// Heavy Attack
class atk_Heavy : public Item_Attack
{
public:
	atk_Heavy(std::string name, sf::Vector2f pos) : Item_Attack(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// ______________CUSTOM DEFENDS__________________

// Light Attack
class dfn_Block : public Item_Defend
{
public:
	dfn_Block(std::string name, sf::Vector2f pos) : Item_Defend(name, pos) {}
	void on_defend_use(std::shared_ptr<Entity> user, bool block);
	void set_display_texts() override;
};

// Heavy Attack
class dfn_Parry : public Item_Defend
{
public:
	dfn_Parry(std::string name, sf::Vector2f pos) : Item_Defend(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};