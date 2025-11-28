#pragma once
#include <vector>
#include <string>
#include <memory> // For pointers
#include "Engine\RenderMan.h"

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

// Left
class Fight0 : public Scene
{
public:
	Fight0(std::string scene_name);
	virtual void on_scene_active();
	virtual void on_scene_inactive();
	virtual void update(const float& dt);
};

// Middle
class Fight1 : public Scene
{
public:
	Fight1(std::string scene_name);
	virtual void on_scene_active();
	virtual void on_scene_inactive();
	virtual void update(const float& dt);
};

// Right
class Fight2 : public Scene
{
public:
	Fight2(std::string scene_name);
	virtual void on_scene_active();
	virtual void on_scene_inactive();
	virtual void update(const float& dt);
};

// Final
class Fight3 : public Scene
{
public:
	Fight3(std::string scene_name);
	virtual void on_scene_active();
	virtual void on_scene_inactive();
	virtual void update(const float& dt);
};

// Settings
class Settings : public Scene
{
public:
	Settings(std::string scene_name);
	virtual void on_scene_active();
	virtual void on_scene_inactive();
	static void set_resolution(int i);
	virtual void update(const float& dt);
private:
	static int current_res_index;
	static const std::vector<sf::VideoMode> resolutions;
	static std::shared_ptr<sf::Text> res_text;
};