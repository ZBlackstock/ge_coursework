#pragma once
#include <vector>
#include <string>
#include <memory> // For pointers
#include "RenderMan.h"

class SceneManager
{
public:
	std::vector<std::shared_ptr<Scene>> scenes;

	void init(); // Stores all scenes, calls init for all scenes too
	void update(const float &dt); // Calls update for active_scene
	void add_scene(std::shared_ptr<Scene> scene);
	void set_active_scene(std::shared_ptr<Scene> scene); // Change to new scene
	std::shared_ptr<Scene> get_active_scene(); // Returns active_scene

private:
	std::shared_ptr<Scene> active_scene; // Current scene
};

class Scene
{
public:
	std::string name;
	RenderMan* render_manager;
	virtual void init(); // Derived class will load sprites and logic specific to itself
	virtual void update(const float &dt);
	virtual void on_scene_active(); // Called when scene is set to active_scene, add SceneMan drawables
	virtual void on_scene_inactive(); // Called on frame when no lonhger active_scene, clear SceneMan drawables
};

class MainMenu : public Scene
{
public:
	MainMenu(string scene_name);
	virtual void init() override;
	virtual void update(const float& dt) override;
};

class Map : public Scene
{
public:
	Map(string scene_name);
	virtual void init() override;
	virtual void update(const float& dt) override;
};