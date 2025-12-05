

class ParticleSystem
{
public:
    ParticleSystem(b2World& world) : physicsWorld(world) {}

    // Spawn particles at position with random direction, size, and force
    void emit(const sf::Vector2f& pos, int amount)
    {
        for (int i = 0; i < amount; ++i)
        {
            // Create Box2D body
            b2BodyDef bodyDef;
            bodyDef.type = b2_dynamicBody;
            bodyDef.position.Set(pos.x / 30.f, pos.y / 30.f); // Box2D uses meters
            b2Body* body = physicsWorld.CreateBody(&bodyDef);

            b2CircleShape circleShape;
            float radius = 5.f + static_cast<float>(rand() % 5); // Random radius 5-10
            circleShape.m_radius = radius / 30.f;

            b2FixtureDef fixtureDef;
            fixtureDef.shape = &circleShape;
            fixtureDef.density = 1.f;
            fixtureDef.friction = 0.3f;
            fixtureDef.restitution = 0.5f; // bouncy
            body->CreateFixture(&fixtureDef);

            // Apply random initial force
            float angle = static_cast<float>(rand() % 360) * b2_pi / 180.f;
            float force = 50.f + static_cast<float>(rand() % 100);
            body->ApplyLinearImpulseToCenter(b2Vec2(force * cos(angle), force * sin(angle)), true);

            // Create drawable
            auto drawable = std::make_shared<sf::CircleShape>(radius);
            drawable->setFillColor(sf::Color::Green);
            drawable->setOrigin(radius, radius);

            particles.push_back({ drawable, body, 5.f }); // 5s lifetime
        }
    }

    // Call this every frame
    void update(float dt)
    {
        // Step physics world
        physicsWorld.Step(dt, 8, 3);

        // Update drawable positions
        for (auto& p : particles)
        {
            b2Vec2 pos = p.body->GetPosition();
            p.drawable->setPosition(pos.x * 30.f, pos.y * 30.f);
            p.lifetime -= dt;
        }

        // Remove particles off-screen or dead
        particles.erase(
            std::remove_if(particles.begin(), particles.end(),
                [this](Particle& p)
                {
                    sf::Vector2f pos = p.drawable->getPosition();
                    bool offScreen = (pos.y > 1080 || pos.x < 0 || pos.x > 1920); // adjust for your window
                    if (offScreen || p.lifetime <= 0.f)
                    {
                        physicsWorld.DestroyBody(p.body);
                        return true;
                    }
                    return false;
                }),
            particles.end()
        );
    }

    const std::vector<Particle>& getParticles() const { return particles; }

private:
    b2World& physicsWorld;
    std::vector<Particle> particles;
};
