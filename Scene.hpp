#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory> // For pointers
#include "Engine\RenderMan.h"
#include "UI_button.hpp"

class Button_KeyBind;

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
	void set_map_sprites();
	void set_map_buttons();
	static bool fight0_victory;
	static bool fight1_victory;
	static bool fight2_victory;
	static bool fight3_victory;
};

// Left
class Fight : public Scene
{
public:
	Fight(std::string scene_name) : Scene(scene_name) {};
	virtual void on_scene_active();
	virtual void on_scene_inactive();
	virtual void update(const float& dt);
	void load_enemy();
	void load_player();

protected:
	static std::shared_ptr<int> player_max_hp;
	static std::shared_ptr<int> player_atk_power;

	std::shared_ptr<std::string> enemy_sprite_name = std::make_shared<std::string>();
	std::shared_ptr<int> enemy_max_hp = std::make_shared<int>();
	std::shared_ptr<int> enemy_atk_pwr = std::make_shared<int>();
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
	static sf::VideoMode get_resolution();
	static int get_resolution_index();
	virtual void update(const float& dt);
	static std::vector<std::shared_ptr<Button_KeyBind>> key_binds;
	static std::vector<sf::VideoMode> resolutions;

private:
	static int current_res_index;
	static std::shared_ptr<sf::Text> res_text;
	static bool _settings_setup;
};

// Death screen
class DeathScreen : public Scene
{
public:
	DeathScreen(std::string scene_name) : Scene(scene_name) {};
	virtual void on_scene_active();
	virtual void on_scene_inactive();
	static void set_resolution(int i);
	virtual void update(const float& dt);

private:
	static float _timer;
};