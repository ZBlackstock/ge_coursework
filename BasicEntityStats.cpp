#include "BasicEntityStats.h"
#include "Engine\ecm.hpp"
#include "RenderMan.h"
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <random>
#include "message_box.hpp"


BasicEntityStats::BasicEntityStats(Entity* p, int max_hp, int atk_power)
	: Component(p),
	base_max_health(max_hp),
	current_health(max_hp),
	base_attack_power(atk_power)
{
}

void BasicEntityStats::update(const float& dt)
{
	for (auto& b : buffs)
		b->update(dt);

	buffs.erase(
		std::remove_if(buffs.begin(), buffs.end(),
			[](auto& b) { return b->expired(); }),
		buffs.end()
	);


	current_health = std::min(current_health, get_max_health());
}

int BasicEntityStats::get_attack_power() const
{
	float mult = 1.0f;
	for (auto& b : buffs)
		mult *= b->attack_power_mult;

	return static_cast<int>(base_attack_power * mult);
}

int BasicEntityStats::get_max_health() const {
	float mult = 1.0f;
	for (auto& b : buffs)
		mult *= b->max_health_mult;

	return static_cast<int>(base_max_health * mult);
}

int BasicEntityStats::get_current_health() const {
	return current_health;
}

void BasicEntityStats::take_damage(int dmg) {
	float mult = 1.0f;
	for (auto& b : buffs)
		mult *= b->take_damage_mult;

	current_health -= static_cast<int>(dmg * mult);
}

void BasicEntityStats::heal(int amount) {
	float mult = 1.0f;
	for (auto& b : buffs)
		mult *= b->heal_amount_mult;

	int heal_amount = static_cast<int>(amount * mult);

	if (current_health < get_max_health()) {
		current_health += heal_amount; // full healing
	}
	else {
		current_health += heal_amount / 2; // 50% effectiveness when overhealing
	}

	// overheal cap
	int max_overheal = static_cast<int>(get_max_health() * 1.5f);
	if (current_health > max_overheal)
		current_health = max_overheal;
}

void BasicEntityStats::take_fire_damage(int dmg)
{
	float mult = 1.0f;
	for (auto& b : buffs)
		mult *= b->fire_attack_power;
	take_damage(static_cast<int>(dmg * mult));
}

void BasicEntityStats::take_sharp_damage(int dmg)
{
	float mult = 1.0f;
	for (auto& b : buffs)
		mult *= b->sharp_attack_power;
	take_damage(static_cast<int>(dmg * mult));
}

void SpriteComponent::set_texure(std::shared_ptr<sf::Texture> tex)
{
	_texture = tex;
	_sprite->setTexture(*_texture);
}
sf::Sprite& SpriteComponent::get_sprite() const { return *_sprite; }


SpriteComponent::SpriteComponent(Entity* p)
	: Component(p), _sprite(std::make_shared<sf::Sprite>()) {
}

void SpriteComponent::update(const float& dt) {

}

void SpriteComponent::render() { RenderMan::createDrawable(_sprite, 1); }


void BasicEntityStats::attack_check(int damage, std::string type)
{
	// Current entity is parrying
	if (blocktype_parry)
	{
		// Parrying, and incoming is heavy -> good chance of deflect
		if (type == "Heavy")
		{
			// 50% chance to reflect damage
			if (rand() % 2 == 0)
			{
				// Reflect damage back to attacker
				auto attackerComps = _parent->get_components<BasicEntityStats>();
				if (!attackerComps.empty())
				{
					BasicEntityStats& attackerStats = *attackerComps[0];
					attackerStats.take_damage(damage);
				}

				MsgBox::set_text("Heavy attack parried! No damage taken!");
			}
			else
			{
				MsgBox::set_text("Heavy attack landed for " + std::to_string(damage) + " damage!");

				// Take full damage if parry fails
				take_damage(damage);
			}
		}   // Parrying, and incoming is light -> bad chance of deflect
		else 
		{
			// 33% chance to reflect damage
			if (rand() % 3 == 0)
			{
				// Reflect damage back to attacker
				auto attackerComps = _parent->get_components<BasicEntityStats>();
				if (!attackerComps.empty())
				{
					BasicEntityStats& attackerStats = *attackerComps[0];
					attackerStats.take_damage(damage);
				}
				MsgBox::set_text("Light attack parried! No damage taken!");

			}
			else
			{
				MsgBox::set_text("Light attack landed for " + std::to_string(damage) + " damage!");

				// Take full damage if parry fails
				take_damage(damage);
			}
		}

	}
	else //entity is blocking 
	{
		// Parrying, and incoming is heavy -> baD chance of deflect
		if (type == "Heavy")
		{
			// 50% chance to reflect damage
			if (rand() % 2 == 0)
			{
				// Reflect damage back to attacker
				auto attackerComps = _parent->get_components<BasicEntityStats>();
				if (!attackerComps.empty())
				{
					BasicEntityStats& attackerStats = *attackerComps[0];
					attackerStats.take_damage(damage/2);
				}
				MsgBox::set_text("Heavy attack blocked! " + std::to_string(damage/2) + " damage taken!");

			}
			else
			{
				MsgBox::set_text("Heavy attack landed for " + std::to_string(damage) + " damage!");

				// Take full damage if parry fails
				take_damage(damage);
			}
		}   // Parrying, and incoming is light -> bad chance of deflect
		else
		{
			// 75% chance to reflect damage
			if (RandomFloat(0, 1) >= 0.25)
			{
				// Reflect damage back to attacker
				auto attackerComps = _parent->get_components<BasicEntityStats>();
				if (!attackerComps.empty())
				{
					BasicEntityStats& attackerStats = *attackerComps[0];
					attackerStats.take_damage(damage/2);
				}
				MsgBox::set_text("Light attack blocked! " + std::to_string(damage / 2) + " damage taken!");
			}
			else
			{
				MsgBox::set_text("Light attack landed for " + std::to_string(damage) + " damage!");

				// Take full damage if parry fails
				take_damage(damage);
			}
		}

	}
}

float BasicEntityStats::RandomFloat(float a, float b) const
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(a, b);
	return dist(gen);
}