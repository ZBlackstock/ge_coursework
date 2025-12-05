#include "ParticleManager.hpp"
#include <cstdlib>
#include <cmath>
#include <box2d/box2d.h>

extern ParticleSystem ps; // your Box2D wrapper

void ParticleManager::emit(const sf::Vector2f& pos, int amount)
{
    for (int i = 0; i < amount; ++i)
    {
        float radius = 5.f + rand() % 5;

        auto drawable = std::make_shared<sf::CircleShape>(radius);
        drawable->setFillColor(sf::Color::Green);
        drawable->setOrigin(radius, radius);
        drawable->setPosition(pos);

        b2BodyDef bodyDef = {};
        bodyDef.type = b2_dynamicBody;
        bodyDef.position = ps.sv2_to_bv2(pos);
        b2BodyId body = b2CreateBody(ps.get_world_id(), &bodyDef);

        b2CircleShape circleShape = {};
        circleShape.radius = radius * ParticleSystem::physics_scale_inv;

        b2FixtureDef fixture = {};
        fixture.shape = &circleShape;
        fixture.density = 1.f;
        fixture.friction = 0.3f;
        fixture.restitution = 0.5f;
        b2Body_CreateFixture(body, &fixture);

        float angle = (rand() % 360) * 3.14159f / 180.f;
        float force = 50.f + rand() % 100;
        b2Body_ApplyLinearImpulseToCenter(body, { force * cos(angle), force * sin(angle) });

        particles.push_back({ drawable, body, 5.f });
    }
}

void ParticleManager::update(float dt)
{
    ps.update(dt);

    for (auto& p : particles)
    {
        b2Vec2 pos = b2Body_GetPosition(p.body);
        p.drawable->setPosition(ps.bv2_to_sv2(pos));
        p.lifetime -= dt;

        if (!addedToRenderMan[p.drawable.get()])
        {
            RenderMan::createDrawable(p.drawable, 10); // top layer
            addedToRenderMan[p.drawable.get()] = true;
        }
    }

    particles.erase(
        std::remove_if(particles.begin(), particles.end(),
            [](Particle& p) {
                sf::Vector2f pos = p.drawable->getPosition();
                bool offscreen = (pos.y > 1080 || pos.x < 0 || pos.x > 1920);
                if (offscreen || p.lifetime <= 0.f)
                    b2DestroyBody(ps.get_world_id(), p.body);
                return offscreen || p.lifetime <= 0.f;
            }),
        particles.end()
    );
}
