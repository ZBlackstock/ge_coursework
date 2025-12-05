#pragma once
#include "ecm.hpp"
#include "Memory.h"
#include "../BasicEntityStats.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

enum class AttackType { Light, Heavy };
enum class BlockType { Block, Parry };

struct Action {
    AttackType attack;
    BlockType block;
};

enum class AIState {
    DecideItem,
    DecideAttack,
    DecideBlock,
    ExecuteAction
};

// Lightweight struct for AI simulation
struct SimulationStats {
    int currentHealth;
    int maxHealth;
    int attackPower;

    SimulationStats(int hp, int atk) : currentHealth(hp), maxHealth(hp), attackPower(atk) {}
};

class AIComponent : public Component {
public:
    explicit AIComponent(Entity* parent, std::shared_ptr<MemoryComponent> memory, Entity* playerEntity);

    void update(const float& dt) override;
    void render() override {}
    void set_State(std::string state);


private:
    AIState currentState = AIState::DecideAttack;
    Entity* playerEntity;

    std::shared_ptr<MemoryComponent> memory;

    // ---- Decision Tree methods ----
    void SimulateTurn(SimulationStats& ai, SimulationStats& player,
        const Action& aiAction, const Action& playerAction);
    std::vector<Action> PredictPlayerActions() const;
    float EvaluateNode(const SimulationStats& ai, const SimulationStats& player) const;
    Action DecideAction(const SimulationStats& aiStats,
        const SimulationStats& playerStats,
        int depth = 2);

    // ---- Execution methods ----
    void ExecuteAttack(const Action& action);
    void ExecuteBlock(const Action& action);
};
