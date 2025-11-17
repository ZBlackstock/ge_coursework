#pragma once
#include <vector>
#include <string>
#include <memory> // For pointers
#include "RenderMan.h"

class Scene
{
public:
	virtual ~Scene() = default;
	std::string name;
	RenderMan* render_manager;
	virtual void init(); // Derived class will load sprites and logic specific to itself
	virtual void update(const float& dt);
	virtual void on_scene_active(); // Called when scene is set to active_scene, add SceneMan drawables
	virtual void on_scene_inactive(); // Called on frame when no lonhger active_scene, clear SceneMan drawables
};

class MainMenu : public Scene
{
public:
	MainMenu(std::string scene_name);
	virtual void on_scene_active();
	virtual void on_scene_inactive();
	virtual void update(const float& dt);
};

class Map : public Scene
{
public:
	Map(std::string scene_name);
	virtual void on_scene_active();
	virtual void on_scene_inactive();
	virtual void update(const float& dt);
};