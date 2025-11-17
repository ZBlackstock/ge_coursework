#include <memory>
#include <vector>
#include <iostream>
#include "SceneMan.hpp"

using sm = SceneManager;
using s = Scene;

// _______________________ Scene Manager ______________________________________________

sm::init()
{
	// Change to have custom scene classes or die
	int i = 0;
	while (i < 5) // Temp loop to handle multiple scenes
	{
		std::shared_ptr<Scene> scene = std::make_shared<Scene>();
		scenes.push_back(scene);
		i++;
	}

	sm::set_active_scene(scenes[0]);
}

// Calls update for active_scene
sm::update(const float& dt)
{
	active_scene->update(dt);
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

s::Scene(std::string scene_name)
{
	name = scene_name;
}

s::update(const float& dt) // Can probably remove this, as update will be hanled by derived classes
{	
}

// ____________________________ Custom Scenes _________________________________________

// NEED:
// main_menu
// map
