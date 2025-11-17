#include <memory>
#include <vector>
#include "SceneMan.hpp"

std::shared_ptr<Scene> SceneManager::get_active_scene()
{
	return active_scene;
}

void SceneManager::set_active_scene(std::shared_ptr<Scene> scene)
{
	active_scene = scene;
}