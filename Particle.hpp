#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <memory>

struct Particle
{
    std::shared_ptr<sf::CircleShape> drawable; // what RenderMan draws
    b2Body* body;  // physics body
    float lifetime; // seconds
};
