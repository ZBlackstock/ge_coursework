#include "Memory.h"
#include "../console.hpp"

MemoryComponent::MemoryComponent(Entity* parent) : Component(parent) {}

float MemoryComponent::RandomFloat(float a, float b) const 
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(a, b);
    return dist(gen);
}

void MemoryComponent::RecordPlayerBlock(bool isHeavy)
{
	Console::print("Recording player block: " + std::to_string(isHeavy));
    float value = isHeavy ? RandomFloat(0.5f, 1.0f) : RandomFloat(0.0f, 0.5f);
    playerBlocks.push_back(value);
    if (playerBlocks.size() > maxMemory) playerBlocks.erase(playerBlocks.begin());
}

void MemoryComponent::RecordPlayerAttack(bool isHeavy)
{
    Console::print("Recording player attack: " + std::to_string(isHeavy));
    float value = isHeavy ? RandomFloat(0.5f, 1.0f) : RandomFloat(0.0f, 0.5f);
    playerAttacks.push_back(value);
    if (playerAttacks.size() > maxMemory) playerAttacks.erase(playerAttacks.begin());
}

float MemoryComponent::GetMedianBlock() const
{
     if (playerBlocks.empty()) return RandomFloat(0.f, 1.f);
    std::vector<float> copy = playerBlocks;
     std::sort(copy.begin(), copy.end());
    size_t mid = copy.size() / 2;
    return copy.size() % 2 == 0 ? (copy[mid - 1] + copy[mid]) / 2.0f : copy[mid];
}

float MemoryComponent::GetMedianAttack() const {
    if (playerAttacks.empty()) return RandomFloat(0.f,1.f);
    std::vector<float> copy = playerAttacks;
    std::sort(copy.begin(), copy.end()); 
    size_t mid = copy.size() / 2;
    return copy.size() % 2 == 0 ? (copy[mid - 1] + copy[mid]) / 2.0f : copy[mid];
}