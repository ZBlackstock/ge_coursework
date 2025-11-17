#pragma once
#include <vector>
#include <string>
#include <memory> // For pointers
#include "Scene.hpp"

class SceneManager
{
public:
	~SceneManager() = default;

	// @brief List of all scenes
	static std::vector<std::shared_ptr<Scene>> scenes;

	// @brief Stores all scenes, and calls init for all scenes
	static void init();
	// @brief Calls update for active_scene
	static void update(const float& dt);
	static void add_scene(std::shared_ptr<Scene> scene);
	// @brief Change to new scene via Shared Pointer
	static void set_active_scene(std::shared_ptr<Scene> scene);
	// @brief Change to new scene via string name
	static void set_active_scene(const std::string& name);
	// @brief Returns active_scene
	static std::shared_ptr<Scene> get_active_scene();

private:
	// @brief The currently active scene
	static std::shared_ptr<Scene> active_scene;
};