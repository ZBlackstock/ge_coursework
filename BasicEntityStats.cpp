#include "BasicEntityStats.h"
#include "Engine\ecm.hpp"
#include "RenderMan.h"
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>


BasicEntityStats::BasicEntityStats(Entity* p, int max_hp, int atk_power)
    : Component(p),
    base_max_health(max_hp),
    current_health(max_hp),
    base_attack_power(atk_power)
{}

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

void death::update(float dt) {}