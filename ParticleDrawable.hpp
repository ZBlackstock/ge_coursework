#pragma once
#include <SFML/Graphics.hpp>
#include "ParticleSystem.hpp"

class ParticleDrawable : public sf::Drawable {
public:
    ~ParticleDrawable() = default;

    ParticleDrawable(const sf::Vector2f& pos, int amount, sf::Color color, float minSpeed, float maxSpeed)
    {
        system.emit(pos, amount, color, minSpeed, maxSpeed);
    }

    void update(float dt)
    {
        system.update(dt);
    }

    bool isAlive() const
    {
        return !system.empty();
    }

private:
    ParticleSystem system;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        system.draw(target, states);
    }
};
