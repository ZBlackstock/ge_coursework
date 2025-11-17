#pragma once
#include <vector>
#include <memory> // For pointers
#include "RenderMan.h"

class SceneManager
{
public:
	std::vector<std::shared_ptr<Scene>> scenes;

	void init() override; // Stores all scenes, calls init for all scenes too
	void update(const float* dt); // Calls update for active_scene

	set_active_scene(std::shared_ptr<Scene> scene); // Change to new scene
	std::shared_ptr<Scene> get_active_scene(); // Returns active_scene

private:
	std::shared_ptr<Scene> active_scene; // Current scene
};

class Scene
{
public:
	RenderMan* render_manager;
	virtual void init(); // Derived class will load sprites and logic specific to itself
	virtual void update(const float* dt);
	virtual void on_scene_active(); // Called when scene is set to active_scene, add SceneMan drawables
	virtual void on_scene_inactive(); // Called on frame when no lonhger active_scene, clear SceneMan drawables
};