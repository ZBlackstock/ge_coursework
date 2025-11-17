#pragma once
#include <vector>
#include <memory> // For pointers
#include "Scene.hpp"

class SceneManager
{
public:
	~SceneManager() = default;
	std::vector<std::shared_ptr<Scene>> scenes;

	// @brief Stores all scenes, and calls init for all scenes
	void init(); // 
	void update(const float& dt); // Calls update for active_scene
	void add_scene(std::shared_ptr<Scene> scene);
	void set_active_scene(std::shared_ptr<Scene> scene); // Change to new scene
	std::shared_ptr<Scene> get_active_scene(); // Returns active_scene

private:
	std::shared_ptr<Scene> active_scene; // Current scene
};