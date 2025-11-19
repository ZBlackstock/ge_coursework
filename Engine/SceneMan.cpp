#include <memory>
#include <vector>
#include <iostream>
#include "SceneMan.hpp"
#include "Scene.hpp"
#include "RenderMan.h"
#include "game_system.h"

using sm = SceneManager;
using gs = GameSystem;
// _______________________ Scene Manager ______________________________________________

// These must be re-declared here because theyre static
std::vector<std::shared_ptr<Scene>> sm::scenes;
std::shared_ptr<Scene> sm::active_scene;

void sm::init()
{
	std::cout << "SceneManager::Init()" << std::endl;
	active_scene = NULL;

	// Declare scenes
	std::shared_ptr<MainMenu> main_menu = std::make_shared<MainMenu>("MainMenu");
	std::shared_ptr<Map> map = std::make_shared<Map>("Map");

	sm::add_scene(main_menu);
	sm::add_scene(map);

	sm::set_active_scene("MainMenu");
}

void sm::update(const float& dt)
{
	if (active_scene != NULL)
	{
		active_scene->update(dt);
	}
}

void sm::add_scene(std::shared_ptr<Scene> scene)
{
	sm::scenes.push_back(scene);
}

std::shared_ptr<Scene> sm::get_active_scene()
{
	return active_scene;
}

void sm::set_active_scene(std::shared_ptr<Scene> scene)
{
	// Clear renderManager list
	if (active_scene != NULL)
	{
		active_scene->on_scene_inactive();
	}
	active_scene = scene;
	active_scene->on_scene_active();
	std::cout << "active_scene = " << scene->name << std::endl;
}

void sm::set_active_scene(const std::string& name)
{
	// Loop through all scenes
	for (int i = 0; i < sm::scenes.size(); ++i)
	{
		std::shared_ptr<Scene> scene = sm::scenes.at(i);
		std::cout << "Comparing string " << name << " to scene_name " << scene.get()->name << std::endl;

		// Compare string name to each scene name
		if (scene.get()->name == name)
		{
			std::cout << "Match!" << std::endl;
			sm::set_active_scene(scene);
			break;
		}
	}
}

// _______________________________ Scene ______________________________________________

void Scene::init() {}
void Scene::update(const float& dt) {}
void Scene::on_scene_active() {}
void Scene::on_scene_inactive() {}

// ____________________________ Custom Scenes _________________________________________


// _______________________MainMenu_________________________________________
MainMenu::MainMenu(std::string scene_name)
{
	name = scene_name;
}

// MOVE THIS TO RENDER MANAGER
// CREATE FUNCTION IN RENDERMAN THAT MAKES SPRITE WITH PATH AND TEXTURE
// create_sprite(string tx_file_path, sf::Vector2f pos, int layer)

// Load sprites for MainMenu HERE
void MainMenu::on_scene_active()
{
	std::cout << "MainMenu on_scene_active()" << std::endl;
	// Load MainMenu sprites
	RenderMan::create_sprite(gs::sprites_path + "title.png", { 0,0 }, 0);
}

bool spacePressed = false;
void MainMenu::update(const float& dt)
{
	// Temporary test for scene changes
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !spacePressed)
	{
		std::cout << "Space key pressed" << std::endl;
		sm::set_active_scene("Map");
		spacePressed = true;
	}
}
void MainMenu::on_scene_inactive()
{
	std::cout << "MainMenu on_scene_inactive()" << std::endl;
}

// _______________________Map_________________________________________
Map::Map(std::string scene_name)
{
	name = scene_name;
}
// Load sprites for Map HERE
void Map::on_scene_active()
{
	std::cout << "Map on_scene_active()" << std::endl;
}
void Map::update(const float& dt)
{

}
void Map::on_scene_inactive()
{
	std::cout << "Map on_scene_inactive()" << std::endl;
}


// NEED TO ADD SCENES FOR FIGHTS
