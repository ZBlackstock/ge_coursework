#pragma once
#include "Particle.hpp"
#include <vector>
#include <memory>
#include <Box2D/Box2D.h>
#include <algorithm>

class ParticleSystem
{
public:
    ParticleSystem(b2World& world) : physicsWorld(world) {}

    // Generate particles
    void emit(const sf::Vector2f& pos, int amount)
    {
        for (int i = 0; i < amount; ++i)
        {
            // Box2D body
            b2BodyDef bodyDef;
            bodyDef.type = b2_dynamicBody;
            bodyDef.position.Set(pos.x / 30.f, pos.y / 30.f); // pixels ? meters
            b2Body* body = physicsWorld.CreateBody(&bodyDef);

            b2CircleShape shape;
            float radius = 5.f + rand() % 5;
            shape.m_radius = radius / 30.f;

            b2FixtureDef fixture;
            fixture.shape = &shape;
            fixture.density = 1.f;
            fixture.friction = 0.3f;
            fixture.restitution = 0.5f; // bounce
            body->CreateFixture(&fixture);

            // Random force
            float angle = (rand() % 360) * b2_pi / 180.f;
            float force = 50.f + rand() % 100;
            body->ApplyLinearImpulseToCenter(b2Vec2(force * cos(angle), force * sin(angle)), true);

            // Drawable
            auto drawable = std::make_shared<sf::CircleShape>(radius);
            drawable->setFillColor(sf::Color::Green);
            drawable->setOrigin(radius, radius);

            particles.push_back({ drawable, body, 5.f });
        }
    }

    // Update physics and lifetime
    void update(float dt)
    {
        physicsWorld.Step(dt, 8, 3);

        for (auto& p : particles)
        {
            b2Vec2 pos = p.body->GetPosition();
            p.drawable->setPosition(pos.x * 30.f, pos.y * 30.f);
            p.lifetime -= dt;
        }

        // Remove off-screen particles
        particles.erase(
            std::remove_if(particles.begin(), particles.end(),
                [this](Particle& p) {
                    sf::Vector2f pos = p.drawable->getPosition();
                    bool offScreen = (pos.y > 1080 || pos.x < 0 || pos.x > 1920);
                    if (offScreen || p.lifetime <= 0.f)
                        physicsWorld.DestroyBody(p.body);
                    return offScreen || p.lifetime <= 0.f;
                }),
            particles.end()
        );
    }

    const std::vector<Particle>& getParticles() const { return particles; }

private:
    b2World& physicsWorld;
    std::vector<Particle> particles;
};
