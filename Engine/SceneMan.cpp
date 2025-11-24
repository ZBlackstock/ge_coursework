#include <memory>
#include <vector>
#include <iostream>
#include "SceneMan.hpp"
#include "Scene.hpp"
#include "RenderMan.h"
#include "game_system.h"
#include "UI_button.hpp"
#include "event_man.hpp"

using sm = SceneManager;
using gs = GameSystem;
using b = Button;
// _______________________ Scene Manager ______________________________________________

// These must be re-declared here because theyre static
std::vector<std::shared_ptr<Scene>> sm::scenes; // Should change this to Map or something
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

// Load sprites for MainMenu HERE
void MainMenu::on_scene_active()
{
	std::cout << "MainMenu on_scene_active()" << std::endl;

	// Load MainMenu sprites
	RenderMan::create_sprite("title.png", { gs::screen_mid.x, gs::screen_mid.y - 200 }, 0);

	std::shared_ptr<Button_LoadScene> btn_play = std::make_shared<Button_LoadScene>
		("play", sf::Vector2f{ gs::screen_mid.x, gs::screen_mid.y + 200.0f }, 1);
	std::shared_ptr<Button_Quit> btn_quit = std::make_shared<Button_Quit>
		("quit", sf::Vector2f{ gs::screen_mid.x,gs::screen_mid.y + 290.0f }, 1);

	btn_play->set_above(btn_quit);
	btn_play->set_below(btn_quit);
	btn_play->set_scene_to_load(SceneManager::scenes[1]); // Map. 

	btn_quit->set_above(btn_play);
	btn_quit->set_below(btn_play);

	EventManager::set_current_button(btn_play);
}

bool spacePressed = false;
void MainMenu::update(const float& dt)
{

}
void MainMenu::on_scene_inactive()
{
	std::cout << "MainMenu on_scene_inactive()" << std::endl;
	RenderMan::RemoveAllDrawObj();
	EventManager::clear_current_button();
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

	// Load map sprite
	RenderMan::create_sprite("map.png", gs::screen_mid, 0);

	// Left fight
	std::shared_ptr<Button> btn_fight_left = std::make_shared<Button>
		("mapButtonLeft", sf::Vector2f{ gs::screen_mid.x - 395, gs::screen_mid.y }, 1);

	// Middle fight
	std::shared_ptr<Button> btn_fight_mid = std::make_shared<Button>
		("mapButtonMid", gs::screen_mid, 1);

	// Right fight
	std::shared_ptr<Button> btn_fight_right = std::make_shared<Button>
		("mapButtonRight", sf::Vector2f{ gs::screen_mid.x + 395, gs::screen_mid.y }, 1);

	// Final fight
	std::shared_ptr<Button> btn_fight_final = std::make_shared<Button>
		("mapButtonBig", sf::Vector2f{ gs::screen_mid.x, gs::screen_mid.y - 350 }, 1);

	EventManager::set_current_button(btn_fight_mid);

	//Set button neighbours
	btn_fight_left->set_above(btn_fight_final);
	btn_fight_left->set_below(btn_fight_final);
	btn_fight_left->set_left(btn_fight_right);
	btn_fight_left->set_right(btn_fight_mid);

	btn_fight_mid->set_above(btn_fight_final);
	btn_fight_mid->set_below(btn_fight_final);
	btn_fight_mid->set_left(btn_fight_left);
	btn_fight_mid->set_right(btn_fight_right);

	btn_fight_right->set_above(btn_fight_final);
	btn_fight_right->set_below(btn_fight_final);
	btn_fight_right->set_left(btn_fight_mid);
	btn_fight_right->set_right(btn_fight_left);

	btn_fight_final->set_above(btn_fight_mid);
	btn_fight_final->set_below(btn_fight_mid);
	btn_fight_final->set_left(btn_fight_left);
	btn_fight_final->set_right(btn_fight_right);
}
void Map::update(const float& dt)
{

}
void Map::on_scene_inactive()
{
	std::cout << "Map on_scene_inactive()" << std::endl;
}


// NEED TO ADD SCENES FOR FIGHTS
