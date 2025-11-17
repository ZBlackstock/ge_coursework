#include <memory>
#include <vector>
#include <iostream>
#include "SceneMan.hpp"

using sm = SceneManager;
using s = Scene;

// _______________________ Scene Manager ______________________________________________

void sm::init()
{
	std::shared_ptr<MainMenu> main_menu = std::make_shared<MainMenu>();
	sm::add_scene(main_menu);

	sm::set_active_scene(main_menu);
}

// Calls update for active_scene
void sm::update(const float& dt)
{
	active_scene->update(dt);
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
	cout << "active_scene = " << scene << endl;
	active_scene = scene;
}

// _______________________________ Scene ______________________________________________

void s::update(const float& dt)
{
}
void s::on_scene_active()
{
}
void s::on_scene_inactive()
{
}

// ____________________________ Custom Scenes _________________________________________

// main_menu
MainMenu::MainMenu(std::string scene_name)
{
	name = scene_name;
}

// Load sprites for MainMenu HERE
MainMenu::init()
{
	cout << "MainMenu init()" << endl;

}

MainMenu::update(const float& dt)
{
	cout << "MainMenu update()" << endl;

}

// map
Map::Map(std::string scene_name)
{
	name = scene_name;
}

// Load sprites for Map HERE
Map::init()
{

}

Map::update(const float& dt)
{

}
