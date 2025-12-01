#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include "ecm.hpp"
#include "decision_tree.hpp"


struct ActionOutput
{   
    //put the ais respons here
};

using ActionFunction = std::function<ActionOutput()>;

struct ActionBehaviours {
    static ActionFunction Attack;
    static ActionFunction Block;
};

class ActionComponent : public Component {
protected:
    Entity* _player;
    float _max_speed;
public:
    void update(const float&) override;
    void move(const sf::Vector2f&);
    void move(float x, float y);
    void render() override {}

    ActionComponent() = delete;
};