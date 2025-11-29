#pragma once
#include "ecm.hpp"


class Buff;

class BasicEntityStats : public Component
{
protected:
    int base_max_health;
    int current_health;
    int base_attack_power;

    std::vector<std::unique_ptr<Buff>> buffs;

public:

    BasicEntityStats(Entity* p, int max_hp, int atk_power);
    

    void update(const float& dt) override;
    int get_max_health() const;
    int get_attack_power() const;
    void take_damage(int dmg);
    void heal(int amount);
    void render() override {}

    template <typename T, typename... Args>
    T* add_buff(Args&&... args) {
        static_assert(std::is_base_of<Buff, T>::value, "T must be a Buff");
        auto buff = std::make_unique<T>(std::forward<Args>(args)...);
        T* ptr = buff.get();
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
    float max_health_mult = 1.0f;
    float attack_power_mult = 1.0f;
    float heal_amount_mult = 1.0f;

    Buff(float duration) : time_remaining(duration) {}
    virtual ~Buff() = default;

    virtual void update(float dt) {
        time_remaining -= dt;
    }

    bool expired() const {
        return time_remaining <= 0.0f;
    }
};

class dath : public Buff {
public:
    dath() : Buff(1000000000.0f) {} // initialize Buff's time_remaining
    void update(float dt); // override if needed
};

class ShapeComponent : public Component {
public:
    ShapeComponent() = delete;
    explicit ShapeComponent(Entity* const p);

    void update(const float& dt) override;
    void render() override;

    sf::Shape& get_shape() const;

    template <typename T, typename... Targs>
    void set_shape(Targs... params) {
        _shape = std::make_shared<T>(params...);
    }
protected:
    std::shared_ptr<sf::Shape> _shape;
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