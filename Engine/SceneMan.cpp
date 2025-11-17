#include <memory>
#include <vector>
#include <iostream>
#include "SceneMan.hpp"
#include "Scene.hpp"


// _______________________ Scene Manager ______________________________________________

void SceneManager::init()
{
	std::cout << "SceneManager::Init()" << std::endl;
	std::shared_ptr<MainMenu> main_menu = std::make_shared<MainMenu>("MainMenu");
	SceneManager::add_scene(main_menu);
	SceneManager::set_active_scene(main_menu);
}

// Calls update for active_scene
void SceneManager::update(const float& dt)
{
	active_scene->update(dt);
}

void SceneManager::add_scene(std::shared_ptr<Scene> scene)
{
	SceneManager::scenes.push_back(scene);
}

std::shared_ptr<Scene> SceneManager::get_active_scene()
{
	return active_scene;
}

void SceneManager::set_active_scene(std::shared_ptr<Scene> scene)
{
	std::cout << "active_scene = " << scene->name << std::endl;
	active_scene->on_scene_inactive();
	active_scene = scene;
	active_scene->on_scene_active();
}

// _______________________________ Scene ______________________________________________

void Scene::init() {}
void Scene::update(const float& dt) {}
void Scene::on_scene_active() {}
void Scene::on_scene_inactive() {}

// ____________________________ Custom Scenes _________________________________________

// main_menu
MainMenu::MainMenu(std::string scene_name)
{
	name = scene_name;
}

// Load sprites for MainMenu HERE
void MainMenu::init()
{
	std::cout << "MainMenu init()" << std::endl;

}

void MainMenu::update(const float& dt)
{
	std::cout << "MainMenu update()" << std::endl;

}

// map
Map::Map(std::string scene_name)
{
	name = scene_name;
}

// Load sprites for Map HERE
void Map::init()
{

}

void Map::update(const float& dt)
{

}
