#pragma once
#include <vector>
#include <memory>
#include <map>
#include "Particle.hpp"
#include "Engine/RenderMan.h"
#include "ParticleSystem.hpp"

class ParticleManager {
public:
    ParticleManager() = default;

    void emit(const sf::Vector2f& pos, int amount);
    void update(float dt);

private:
    std::vector<Particle> particles;
    std::map<sf::Drawable*, bool> addedToRenderMan;
};
