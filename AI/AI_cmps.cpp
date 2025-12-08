#include "AI_cmps.h"
#include "../console.hpp"
#include "../item_man.hpp"
#include "../fight_manager.hpp"
#include "../message_box.hpp"


// -----------------
// Constructor
// -----------------
AIComponent::AIComponent(Entity* parent, std::shared_ptr<MemoryComponent> memory, Entity* playerEntity,int depth)
	: Component(parent), memory(memory), playerEntity(playerEntity), mem_depth(depth)
{
}

// -----------------
// State Machine Update
// -----------------
void AIComponent::update(const float& dt) {
	// Get stats from real components

	auto statsComp = _parent->get_components<BasicEntityStats>();
	if (statsComp.empty()) return;
	BasicEntityStats& aiStats = *statsComp[0];

	// Player stats
	auto playerStatsComp = playerEntity->get_components<BasicEntityStats>();
	if (playerStatsComp.empty()) return;
	BasicEntityStats& playerStats = *playerStatsComp[0];
	switch (currentState) {
	case AIState::DecideItem:
		// TODO: implement item choice
		std::cout << "AI deciding item...\n";
		currentState = AIState::DecideAttack;
		break;

	case AIState::DecideAttack: {
		// Create simulation copies
		SimulationStats aiSim(aiStats.get_current_health(), aiStats.get_attack_power());
		SimulationStats playerSim(playerStats.get_current_health(), playerStats.get_attack_power());

		// Decide best action using simulation
		Action attackAction = DecideAction(aiSim, playerSim, mem_depth);

		ExecuteAttack(attackAction);
		currentState = AIState::DecideBlock;
		break;
	}

	case AIState::DecideBlock: {
		SimulationStats aiSim(aiStats.get_max_health(), aiStats.get_attack_power());
		SimulationStats playerSim(playerStats.get_max_health(), playerStats.get_attack_power());

		Action blockAction = DecideAction(aiSim, playerSim, mem_depth); 

		ExecuteBlock(blockAction);
		currentState = AIState::ExecuteAction;
		break;
	}

	case AIState::ExecuteAction:
		currentState = AIState::DecideItem;
		break;
	}
}

//state changer
void AIComponent::set_State(std::string state)
{
	if (state == "Item")
	{
		currentState = AIState::DecideItem;
	}
	else if (state == "Attack")
	{
		currentState = AIState::DecideAttack;
	}
	else if (state == "Block")
	{
		currentState = AIState::DecideBlock;
	}
	else
	{
		Console::print("error invalid state");
	}
}

// -----------------
// Execution
// -----------------
void AIComponent::ExecuteAttack(const Action& action) {
	std::cout << "AI attacks with "
		<< (action.attack == AttackType::Light ? "Light" : "Heavy")
		<< "\n";

	bool isHeavy = (action.attack == AttackType::Heavy);
	std::string type;
	if (isHeavy = true) 
	{
		type = "Heavy";
	}
	else
	{
		type = "Light";
	}
	ItemManager::get_player()->get_compatible_components<BasicEntityStats>()[0]->attack_check(ItemManager::get_enemy()->get_compatible_components<BasicEntityStats>()[0]->get_attack_power(),type );
	FightManager::set_enemy_attacked(true);

	//notify player of AI attack
	if ((action.attack == AttackType::Light))
	{
		MsgBox::set_text("enemy attacks with Light");
	}
	else 
	{
		MsgBox::set_text("enemy attacks with Heavy");
	}
}

void AIComponent::ExecuteBlock(const Action& action) {
	std::cout << "AI blocks with "
		<< (action.block == BlockType::Block ? "Light" : "Heavy")
		<< "\n";
	FightManager::set_enemy_defended(true);
	bool isParry = (action.block == BlockType::Parry);
	ItemManager::get_enemy()->get_compatible_components<BasicEntityStats>()[0]->blocktype_parry = isParry;
	MsgBox::set_text("enemy has used a Block");
	
}

// -----------------
// Decision Tree Logic
// -----------------
void AIComponent::SimulateTurn(SimulationStats& ai, SimulationStats& player,
	const Action& aiAction, const Action& playerAction) {
	// AI attacks player
	int aiDamage = (aiAction.attack == AttackType::Light ? 10 : 20);
	int playerBlock = (playerAction.block == BlockType::Block ? 5 : 15);
	int netDamageToPlayer = std::max(aiDamage - playerBlock, 0);
	player.currentHealth = std::max(player.currentHealth - netDamageToPlayer, 0);

	// Player attacks AI
	int playerDamage = (playerAction.attack == AttackType::Light ? 10 : 20);
	int aiBlock = (aiAction.block == BlockType::Block ? 5 : 15);
	int netDamageToAI = std::max(playerDamage - aiBlock, 0);
	ai.currentHealth = std::max(ai.currentHealth - netDamageToAI, 0);
}

std::vector<Action> AIComponent::PredictPlayerActions() const {
	std::vector<Action> predictions;

	float medianBlock = memory->GetMedianBlock();
	float medianAttack = memory->GetMedianAttack();
	predictions.push_back({
		medianAttack < 1.f ? AttackType::Light : AttackType::Heavy,
		medianBlock < 0.5f ? BlockType::Block : BlockType::Parry
		});

	return predictions;
}


//node for the Attach/block decision tree
float AIComponent::EvaluateNode(const SimulationStats& ai, const SimulationStats& player) const {
	return (player.maxHealth - player.currentHealth) - (ai.maxHealth - ai.currentHealth);
}

Action AIComponent::DecideAction(const SimulationStats& aiStats,
	const SimulationStats& playerStats,
	int depth)
{
	Action bestAction;
	float bestScore = -1e9f;

	// Base case: if depth = 0, return a default action
	if (depth <= 0) {
		return { AttackType::Light, BlockType::Block };
	}

	// Generate all possible AI actions
	for (auto aiAttack : { AttackType::Light, AttackType::Heavy }) {
		for (auto aiBlock : { BlockType::Block, BlockType::Parry }) {
			Action aiAction = { aiAttack, aiBlock };

			// Predict possible player responses
			for (auto playerAction : PredictPlayerActions()) {
				// Copy stats for simulation
				SimulationStats aiCopy = aiStats;
				SimulationStats playerCopy = playerStats;

				// Simulate this turn
				SimulateTurn(aiCopy, playerCopy, aiAction, playerAction);

				float score = -1e9f;
				if (depth > 1) {
					// Recursive lookahead: simulate AI's next turn
					Action nextAction = DecideAction(aiCopy, playerCopy, depth - 1);
					SimulationStats aiNext = aiCopy;
					SimulationStats playerNext = playerCopy;
					// Simulate next turn
					for (auto playerNextAction : PredictPlayerActions()) {
						SimulateTurn(aiNext, playerNext, nextAction, playerNextAction);
						float nextScore = EvaluateNode(aiNext, playerNext);
						if (nextScore > score) score = nextScore;
					}
				}
				else {
					// Leaf node: evaluate current turn
					score = EvaluateNode(aiCopy, playerCopy);
				}

				if (score > bestScore) {
					bestScore = score;
					bestAction = aiAction;
					Console::print("Best action updated: Attack "
						+ std::string(aiAction.attack == AttackType::Light ? "Light" : "Heavy")
						+ ", Block " + std::string(aiAction.block == BlockType::Block ? "Block" : "Parry"));
				}
			}
		}
	}

	return bestAction;
}