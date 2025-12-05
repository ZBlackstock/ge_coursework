#pragma once
#include <SFML/Graphics.hpp>
#include "ParticleSystem.hpp"
#include <box2d/box2d.h>

struct Particle {
    std::shared_ptr<sf::CircleShape> drawable; // what RenderMan draws
    b2BodyId body;                             // Box2D body
    float lifetime;                             // seconds
};
