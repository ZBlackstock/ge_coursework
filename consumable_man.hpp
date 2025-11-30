#pragma once
#include <memory>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "UI_button.hpp"

// Forward definition
class Consumable;
class Button_Consumable;

class ConsumableManager
{
public:
	static std::vector<std::shared_ptr<Consumable>> all_consumables;
	static std::vector<std::shared_ptr<Consumable>> player_consumables;
	static void init();
	static void visible(bool visible);
	static int num_player_consumables;
};

class Consumable
{
public:
	Consumable(std::string name, sf::Vector2f pos);

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

// Heal player by amount
class cns_HealingPotion : public Consumable
{
public:
	cns_HealingPotion(std::string name, sf::Vector2f pos, int heal_amount) : Consumable(name, pos), _heal_amount(heal_amount) {}
	void on_use() override;
	void set_display_texts() override;

private:
	int _heal_amount;
};

// Resistant to next fire damage dealt
class cns_FireResistance : public Consumable
{
public:
	cns_FireResistance(std::string name, sf::Vector2f pos, int resistance) : Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;

private:
	int _resistance;
};

// Resistant to next sharp damage dealt
class cns_SharpResistance : public Consumable
{
public:
	cns_SharpResistance(std::string name, sf::Vector2f pos, int resistance) : Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;

private:
	int _resistance;
};

// Resistant to next blunt damage dealt
class cns_FireBomb : public Consumable
{
public:
	cns_FireBomb(std::string name, sf::Vector2f pos, int damage) : Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;

private:
	int _damage;
};

// If enemy's next attack lands, it will deal half of recieved damage to the enemy
class cns_Thorns : public Consumable
{
public:
	cns_Thorns(std::string name, sf::Vector2f pos) : Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// Enemy's next attack double likely to miss
class cns_Illusion : public Consumable
{
public:
	cns_Illusion(std::string name, sf::Vector2f pos) : Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// Next player attack will deal additional fire damage
class cns_FireBlessing : public Consumable
{
public:
	cns_FireBlessing(std::string name, sf::Vector2f pos) : Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// Next player attack will deal additional sharp damage
class cns_Whetstone : public Consumable
{
public:
	cns_Whetstone(std::string name, sf::Vector2f pos) : Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// Next player attack will deal double damage, but is less likely to land
class cns_Rage : public Consumable
{
public:
	cns_Rage(std::string name, sf::Vector2f pos) : Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// Next player parry is more likely to be successful
class cns_QuickEye : public Consumable
{
public:
	cns_QuickEye(std::string name, sf::Vector2f pos) : Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};

// If enemy performs fire attack, they will take the fire damage
class cns_Oil : public Consumable
{
public:
	cns_Oil(std::string name, sf::Vector2f pos) : Consumable(name, pos) {}
	void on_use() override;
	void set_display_texts() override;
};