#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory> // For pointers
#include "Engine\RenderMan.h"

class Scene
{
public:
	Scene(std::string scene_name);
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
	MainMenu(std::string scene_name) : Scene(scene_name) {};
	virtual void on_scene_active();
	virtual void on_scene_inactive();
	virtual void update(const float& dt);
};

class Map : public Scene
{
public:
	Map(std::string scene_name) : Scene(scene_name) {};
	virtual void on_scene_active();
	virtual void on_scene_inactive();
	virtual void update(const float& dt);
};

// Left
class Fight : public Scene
{
public:
	Fight(std::string scene_name) : Scene(scene_name) {};
	virtual void on_scene_active();
	virtual void on_scene_inactive();
	virtual void update(const float& dt);
};

// Left
class Fight0 : public Fight
{
public:
	Fight0(std::string scene_name) : Fight(scene_name) {};
	void on_scene_active() override;
	void on_scene_inactive() override;
	void update(const float& dt);
};

// Middle
class Fight1 : public Fight
{
public:
	Fight1(std::string scene_name) : Fight(scene_name) {};
	void on_scene_active() override;
	void on_scene_inactive() override;
	void update(const float& dt);
};

// Right
class Fight2 : public Fight
{
public:
	Fight2(std::string scene_name) : Fight(scene_name) {};
	void on_scene_active() override;
	void on_scene_inactive() override;
	void update(const float& dt);
};

// Final
class Fight3 : public Fight
{
public:
	Fight3(std::string scene_name) : Fight(scene_name) {};
	void on_scene_active() override;
	void on_scene_inactive() override;
	void update(const float& dt);
};

// Settings
class Settings : public Scene
{
public:
	Settings(std::string scene_name) : Scene(scene_name) {};
	virtual void on_scene_active();
	virtual void on_scene_inactive();
	static void set_resolution(int i);
	virtual void update(const float& dt);

private:
	static int current_res_index;
	static const std::vector<sf::VideoMode> resolutions;
	static std::shared_ptr<sf::Text> res_text;
};