#pragma once
#include "ecm.hpp"


class Buff;

class BasicEntityStats : public Component
{
protected:
	int base_max_health;
	int base_attack_power;


public:
	BasicEntityStats(Entity* p, int max_hp, int atk_power);

	int current_health;
	bool blocktype_parry = false;
	std::vector<std::unique_ptr<Buff>> buffs;

	void update(const float& dt) override;
	int get_current_health() const;
	int get_attack_power() const;
	int get_max_health() const;
	void take_damage(int dmg);
	void heal(int amount);
	void render() override {}
	float RandomFloat(float a, float b) const;

	void attack_check(int damage, std::string type);

	template <typename Type, typename... Args>
	Type* add_buff(Args&&... args) {
		static_assert(std::is_base_of<Buff, Type>::value, "Type must be a Buff");
		auto buff = std::make_unique<Type>(std::forward<Args>(args)...);
		Type* ptr = buff.get();
		buffs.push_back(std::move(buff));
		return ptr;
	}
};

class Buff
{
protected:
	float time_remaining;

public:
	float take_damage_mult = 1.0f;
	float attack_power_mult = 1.0f;
	float heal_amount_mult = 1.0f;

	Buff() = default;
	Buff(int index, float mult)
	{
		if (index == 0)
		{
			take_damage_mult = mult;
		}
		else if (index == 1)
		{
			attack_power_mult = mult;
		}
		else if (index == 2)
		{
			heal_amount_mult = mult;
		}
	};
	virtual ~Buff() = default;

	virtual void update(float dt) {
		//time_remaining -= dt;
	}

	bool expired() const {
		return time_remaining <= 0.0f;
	}
};


class SpriteComponent : public Component {
protected:
	std::shared_ptr<sf::Sprite> _sprite;
	std::shared_ptr<sf::Texture> _texture;
public:
	SpriteComponent() = delete;

	explicit SpriteComponent(Entity* p);
	void update(const float& dt) override;
	void render() override;

	sf::Sprite& get_sprite() const;


	void set_texure(std::shared_ptr<sf::Texture> tex);
};