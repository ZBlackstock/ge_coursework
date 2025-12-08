#pragma once
#include "ecm.hpp"
#include <vector>
#include <random>


class MemoryComponent : public Component {
public:
    explicit MemoryComponent(Entity* parent);
    ~MemoryComponent() override = default;

    void update(const float& dt) override {}
    void render() override {}

    void RecordPlayerBlock(bool isHeavy);
    void RecordPlayerAttack(bool isHeavy);
    float GetMedianBlock() const;
    float GetMedianAttack() const;

    std::vector<float> playerBlocks;
    std::vector<float> playerAttacks;

private:
    size_t maxMemory = 20;

    float RandomFloat(float a, float b) const;
};