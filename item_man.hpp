#pragma once
#include <memory>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "UI_button.hpp"

// Forward definition
class Item;
class Button_Consumable;

class ItemManager
{
public:
	static std::vector<std::shared_ptr<Item>> all_consumables;
	static std::vector<std::shared_ptr<Item>> player_consumables;
	static std::vector<std::shared_ptr<Item>> player_attacks;
	static void init();
	static void visible(std::vector<std::shared_ptr<Item>> list, bool visible);
	static int num_player_consumables;
};

class Item
{
public:
	Item(std::string name, sf::Vector2f pos);

	std::shared_ptr<Button_Consumable> button = nullptr;
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

// ______________CUSTOM CONSUMABLES__________________

// Heal player by amount
class cns_HealingPotion : public Item
{
public:
	cns_HealingPotion(std::string name, sf::Vector2f pos, int heal_amount) : Item(name, pos), _heal_amount(heal_amount) {}
	void on_use() override;
	void set_display_texts() override;

private:
	int _heal_amount;
};

// Resistant to next fire damage dealt
class cns_FireResistance : public Item
{
public:
	cns_FireResistance(std::string name, sf::Vector2f pos, int resistance) : Item(name, pos) {}
	void on_use() override;
	void set_display_texts() override;

private:
	int _resistance;
};

// Resistant to next sharp damage dealt
class cns_SharpResistance : public Item
{
public:
	cns_SharpResistance(std::string name, sf::Vector2f pos, int resistance) : Item(name, pos) {}
	void on_use() override;
	void set_display_texts() override;

private:
	int _resistance;
};

// Resistant to next blunt damage dealt
class cns_FireBomb : public Item
{
public:
	cns_FireBomb(std::string name, sf::Vector2f pos, int damage) : Item(name, pos) {}
	void on_use() override;
	void set_display_texts() override;

private:
	int _damage;
};

// If enemy's next attack lands, it will deal half of recieved damage to the enemy
class cns_Thorns : public Item
{
public:
	cns_Thorns(std::string name, sf::Vector2f pos) : Item(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// Enemy's next attack double likely to miss
class cns_Illusion : public Item
{
public:
	cns_Illusion(std::string name, sf::Vector2f pos) : Item(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// Next player attack will deal additional fire damage
class cns_FireBlessing : public Item
{
public:
	cns_FireBlessing(std::string name, sf::Vector2f pos) : Item(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// Next player attack will deal additional sharp damage
class cns_Whetstone : public Item
{
public:
	cns_Whetstone(std::string name, sf::Vector2f pos) : Item(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// Next player attack will deal double damage, but is less likely to land
class cns_Rage : public Item
{
public:
	cns_Rage(std::string name, sf::Vector2f pos) : Item(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// Next player parry is more likely to be successful
class cns_QuickEye : public Item
{
public:
	cns_QuickEye(std::string name, sf::Vector2f pos) : Item(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// If enemy performs fire attack, they will take the fire damage
class cns_Oil : public Item
{
public:
	cns_Oil(std::string name, sf::Vector2f pos) : Item(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// ______________CUSTOM ATTACKS__________________

// Light Attack
class atk_Light : public Item
{
public:
	atk_Light(std::string name, sf::Vector2f pos) : Item(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// Heavy Attack
class atk_Heavy : public Item
{
public:
	atk_Heavy(std::string name, sf::Vector2f pos) : Item(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};