#include <memory>
#include <vector>
#include <iostream>
#include "SceneMan.hpp"
#include "Scene.hpp"
#include "RenderMan.h"
#include "game_system.hpp"
#include "UI_button.hpp"
#include "event_man.hpp"
#include "UI_exit_to_mainmenu.hpp"
#include "input_man.hpp"
#include "item_man.hpp"
#include "message_box.hpp"
#include "fight_manager.hpp"

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
	//Fight Scenes
	std::shared_ptr<Fight0> fight0 = std::make_shared<Fight0>("Fight0"); // Left
	std::shared_ptr<Fight1> fight1 = std::make_shared<Fight1>("Fight1"); // Middle
	std::shared_ptr<Fight2> fight2 = std::make_shared<Fight2>("Fight2"); // Right
	std::shared_ptr<Fight3> fight3 = std::make_shared<Fight3>("Fight3"); // Final

	std::shared_ptr<Settings> settings = std::make_shared<Settings>("Settings"); // Settings


	sm::add_scene(main_menu);
	sm::add_scene(map);
	sm::add_scene(fight0);
	sm::add_scene(fight1);
	sm::add_scene(fight2);
	sm::add_scene(fight3);
	sm::add_scene(settings);

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
	for (int ic = 0; ic < sm::scenes.size(); ++ic)
	{
		std::shared_ptr<Scene> scene = sm::scenes.at(ic);
		std::cout << "Comparing string " << name << " to scne_name " << scene.get()->name << std::endl;

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

// Need to declare these to avoid LNK error. These are only used by inherited classes
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
	std::shared_ptr<Button_LoadScene> btn_settings = std::make_shared<Button_LoadScene>
		("settings", sf::Vector2f{ gs::screen_mid.x, gs::screen_mid.y + 290.0f }, 1);
	std::shared_ptr<Button_Quit> btn_quit = std::make_shared<Button_Quit>
		("quit", sf::Vector2f{ gs::screen_mid.x, gs::screen_mid.y + 380.0f }, 1);

	btn_play->set_above(btn_quit);
	btn_play->set_below(btn_settings);
	btn_play->set_scene_to_load(SceneManager::scenes[1]); // Map. 

	btn_settings->set_above(btn_play);
	btn_settings->set_below(btn_quit);
	btn_settings->set_scene_to_load(SceneManager::scenes[6]); // Settings

	btn_quit->set_above(btn_settings);
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

std::shared_ptr<Button_LoadScene> sm::btn_fight_left = nullptr;
std::shared_ptr<Button_LoadScene> sm::btn_fight_mid = nullptr;
std::shared_ptr<Button_LoadScene> sm::btn_fight_right = nullptr;
std::shared_ptr<Button_LoadScene> sm::btn_fight_final = nullptr;

// Load sprites for Map HERE
void Map::on_scene_active()
{
	std::cout << "Map on_scene_active()" << std::endl;

	ExitToMainMenu::init();

	// Load map sprite
	RenderMan::create_sprite("map.png", gs::screen_mid, 0);

	// Left fight
	sm::btn_fight_left = std::make_shared<Button_LoadScene>
		("mapButtonLeft", sf::Vector2f{ gs::screen_mid.x - 395, gs::screen_mid.y }, 1);

	// Middle fight
	sm::btn_fight_mid = std::make_shared<Button_LoadScene>
		("mapButtonMid", gs::screen_mid, 1);

	// Right fight
	sm::btn_fight_right = std::make_shared<Button_LoadScene>
		("mapButtonRight", sf::Vector2f{ gs::screen_mid.x + 395, gs::screen_mid.y }, 1);

	// Final fight
	sm::btn_fight_final = std::make_shared<Button_LoadScene>
		("mapButtonBig", sf::Vector2f{ gs::screen_mid.x, gs::screen_mid.y - 350 }, 1);

	EventManager::set_current_button(sm::btn_fight_mid);

	//Set button neighbours
	sm::btn_fight_left->set_above(sm::btn_fight_final);
	sm::btn_fight_left->set_below(sm::btn_fight_final);
	sm::btn_fight_left->set_left(sm::btn_fight_right);
	sm::btn_fight_left->set_right(sm::btn_fight_mid);

	sm::btn_fight_mid->set_above(sm::btn_fight_final);
	sm::btn_fight_mid->set_below(sm::btn_fight_final);
	sm::btn_fight_mid->set_left(sm::btn_fight_left);
	sm::btn_fight_mid->set_right(sm::btn_fight_right);

	sm::btn_fight_right->set_above(sm::btn_fight_final);
	sm::btn_fight_right->set_below(sm::btn_fight_final);
	sm::btn_fight_right->set_left(sm::btn_fight_mid);
	sm::btn_fight_right->set_right(sm::btn_fight_left);

	sm::btn_fight_final->set_above(sm::btn_fight_mid);
	sm::btn_fight_final->set_below(sm::btn_fight_mid);
	sm::btn_fight_final->set_left(sm::btn_fight_left);
	sm::btn_fight_final->set_right(sm::btn_fight_right);

	//Set button attached scenes
	sm::btn_fight_left->set_scene_to_load(SceneManager::scenes[2]);
	sm::btn_fight_mid->set_scene_to_load(SceneManager::scenes[3]);
	sm::btn_fight_right->set_scene_to_load(SceneManager::scenes[4]);
	sm::btn_fight_final->set_scene_to_load(SceneManager::scenes[5]);

}
void Map::update(const float& dt)
{
	if (InputManager::press_menu())
	{
		ExitToMainMenu::set_active(!ExitToMainMenu::get_active());

		if (!ExitToMainMenu::get_active())
		{
			EventManager::set_current_button(sm::btn_fight_mid);
		}
	}
}
void Map::on_scene_inactive()
{
	std::cout << "Map on_scene_inactive()" << std::endl;
	RenderMan::RemoveAllDrawObj();
	EventManager::clear_current_button();
}


// NEXT:
// - UI Sprites. Douglas do enemy designs before make enemy sprites?
// - Press esc for main menu. Put code for this in its own script probs. "UI_exit_to_menu" or something

// _______________________Fight0 (Left)_________________________________________
Fight0::Fight0(std::string scene_name)
{
	name = scene_name;
}
// Load sprites for Map HERE
void Fight0::on_scene_active()
{
	FightManager::init();
	ItemManager::init();
	ExitToMainMenu::init();
	MsgBox::init();
	EventManager::set_current_button(ItemManager::player_consumables[0]->button);
	RenderMan::create_sprite("knight_sprite.png", {(gs::screen_mid.x + gs::screen_mid.x) - 500, (gs::screen_mid.y - 200)}, 1);
}
void Fight0::update(const float& dt)
{
	if (InputManager::press_menu())
	{
		ExitToMainMenu::set_active(!ExitToMainMenu::get_active());

		if (!ExitToMainMenu::get_active())
		{
			EventManager::set_current_button(ItemManager::player_consumables[0]->button);
		}
	}

	FightManager::update(dt);
}
void Fight0::on_scene_inactive()
{
	std::cout << "Fight0 (Left) on_scene_inactive()" << std::endl;
	RenderMan::RemoveAllDrawObj();
	EventManager::clear_current_button();
}

// _______________________Fight1 (Middle)_________________________________________
Fight1::Fight1(std::string scene_name)
{
	name = scene_name;
}
// Load sprites for Map HERE
void Fight1::on_scene_active()
{
	MsgBox::init();
	RenderMan::create_sprite("meatball_monster_sprite.png", { (gs::screen_mid.x + gs::screen_mid.x) - 500, (gs::screen_mid.y - 200) }, 1);
}
void Fight1::update(const float& dt)
{

}
void Fight1::on_scene_inactive()
{
	std::cout << "Fight1 (Middle) on_scene_inactive()" << std::endl;
	RenderMan::RemoveAllDrawObj();
	EventManager::clear_current_button();
}

// _______________________Fight2 (Right)_________________________________________
Fight2::Fight2(std::string scene_name)
{
	name = scene_name;

}
// Load sprites for Map HERE
void Fight2::on_scene_active()
{
	MsgBox::init();
	RenderMan::create_sprite("skinny_zombie_sprite.png", { (gs::screen_mid.x + gs::screen_mid.x) - 500, (gs::screen_mid.y - 200) }, 1);
}
void Fight2::update(const float& dt)
{

}
void Fight2::on_scene_inactive()
{
	std::cout << "Fight2 (Right) on_scene_inactive()" << std::endl;
	RenderMan::RemoveAllDrawObj();
	EventManager::clear_current_button();
}

// _______________________Fight3 (Final)_________________________________________
Fight3::Fight3(std::string scene_name)
{
	name = scene_name;
}
// Load sprites for Map HERE
void Fight3::on_scene_active()
{
	MsgBox::init();
	RenderMan::create_sprite("black_dragon_sprite.png", { (gs::screen_mid.x + gs::screen_mid.x) - 500, (gs::screen_mid.y - 200) }, 1);
}
void Fight3::update(const float& dt)
{

}
void Fight3::on_scene_inactive()
{
	std::cout << "Fight3 (Final) on_scene_inactive()" << std::endl;
	RenderMan::RemoveAllDrawObj();
	EventManager::clear_current_button();
}

// _______________________Settings_________________________________________
Settings::Settings(std::string scene_name)
{
	name = scene_name;
}

int Settings::current_res_index = 1;
const std::vector<sf::VideoMode> Settings::resolutions = sf::VideoMode::getFullscreenModes();;
std::shared_ptr<sf::Text> Settings::res_text = std::make_shared<sf::Text>();

// Make Button_KeyBind

// Initiate Settings
void Settings::on_scene_active()
{
	// Load sprite
	RenderMan::create_sprite("settings.png", gs::screen_mid, 0);

	// Load back button and fullscreen toggle
	std::shared_ptr<Button_LoadScene> btn_back = std::make_shared<Button_LoadScene>
		("back", sf::Vector2f{ gs::screen_mid.x, gs::screen_mid.y + 380.0f }, 1);
	std::shared_ptr<Button_ToggleFullscreen> btn_togglefullscreen = std::make_shared<Button_ToggleFullscreen>
		("togglefullscreen", sf::Vector2f{ gs::screen_mid.x, gs::screen_mid.y + 290.0f }, 1);

	// Load resolution arrows buttons
	std::shared_ptr<Button_SetResolution> btn_res_arrow_left = std::make_shared<Button_SetResolution>
		("arrow_left", sf::Vector2f{ 960, 680 }, 1);
	btn_res_arrow_left->set_change(-1);

	std::shared_ptr<Button_SetResolution> btn_res_arrow_right = std::make_shared<Button_SetResolution>
		("arrow_right", sf::Vector2f{ 1480,680 }, 1);
	btn_res_arrow_left->set_change(1);

	// Load Keybind buttons
	std::shared_ptr<Button_KeyBind> btn_key_bind_select = std::make_shared<Button_KeyBind>
		("settings_select", sf::Vector2f{ 1100,200 }, 1);
	btn_key_bind_select->set_input(InputManager::submit);
	btn_key_bind_select->txt_pos = sf::Vector2f{ 1450,170 };
	btn_key_bind_select->text_init();

	std::shared_ptr<Button_KeyBind> btn_key_bind_up = std::make_shared<Button_KeyBind>
		("settings_up", sf::Vector2f{ 1100,250 }, 1);
	btn_key_bind_up->set_input(InputManager::up);
	btn_key_bind_up->txt_pos = sf::Vector2f{ 1450,240 };
	btn_key_bind_up->text_init();

	std::shared_ptr<Button_KeyBind> btn_key_bind_down = std::make_shared<Button_KeyBind>
		("settings_down", sf::Vector2f{ 1100,310 }, 1);
	btn_key_bind_down->set_input(InputManager::down);
	btn_key_bind_down->txt_pos = sf::Vector2f{ 1450,310 };
	btn_key_bind_down->text_init();

	std::shared_ptr<Button_KeyBind> btn_key_bind_left = std::make_shared<Button_KeyBind>
		("settings_left", sf::Vector2f{ 1100,390 }, 1);
	btn_key_bind_left->set_input(InputManager::left);
	btn_key_bind_left->txt_pos = sf::Vector2f{ 1450,390 };
	btn_key_bind_left->text_init();

	std::shared_ptr<Button_KeyBind> btn_key_bind_right = std::make_shared<Button_KeyBind>
		("settings_right", sf::Vector2f{ 1100,460 }, 1);
	btn_key_bind_right->set_input(InputManager::right);
	btn_key_bind_right->txt_pos = sf::Vector2f{ 1450,460 };
	btn_key_bind_right->text_init();

	// Assign back button scene and set it to highlighted
	EventManager::set_current_button(btn_togglefullscreen);
	btn_back->set_scene_to_load(SceneManager::scenes[0]); // Main Menu

	btn_togglefullscreen->set_above(btn_res_arrow_left);
	btn_togglefullscreen->set_below(btn_back);

	btn_back->set_above(btn_togglefullscreen);
	btn_back->set_below(btn_key_bind_select);

	btn_res_arrow_left->set_left(btn_res_arrow_right);
	btn_res_arrow_left->set_right(btn_res_arrow_right);
	btn_res_arrow_left->set_below(btn_togglefullscreen);
	btn_res_arrow_left->set_above(btn_key_bind_right);

	btn_res_arrow_right->set_left(btn_res_arrow_left);
	btn_res_arrow_right->set_right(btn_res_arrow_left);
	btn_res_arrow_right->set_below(btn_togglefullscreen);
	btn_res_arrow_right->set_above(btn_key_bind_right);

	btn_key_bind_select->set_above(btn_back);
	btn_key_bind_select->set_below(btn_key_bind_up);

	btn_key_bind_up->set_above(btn_key_bind_select);
	btn_key_bind_up->set_below(btn_key_bind_down);

	btn_key_bind_down->set_above(btn_key_bind_up);
	btn_key_bind_down->set_below(btn_key_bind_left);

	btn_key_bind_left->set_above(btn_key_bind_down);
	btn_key_bind_left->set_below(btn_key_bind_right);

	btn_key_bind_right->set_above(btn_key_bind_left);
	btn_key_bind_right->set_below(btn_res_arrow_left);

	// Set current resolution text
	Settings::res_text->setString(std::to_string(Settings::resolutions[Settings::current_res_index].width)
		+ " X " + std::to_string(Settings::resolutions[Settings::current_res_index].height));
	Settings::res_text->setFont(gs::font_bold);
	Settings::res_text->setOrigin(Settings::res_text->getScale().x / 2, Settings::res_text->getScale().y / 2);
	Settings::res_text->setPosition(1100, 650);
	Settings::res_text->setColor(sf::Color::White);
	Settings::res_text->setCharacterSize(40);
	RenderMan::createDrawable(Settings::res_text, 2);
}

void Settings::update(const float& dt)
{

}


void Settings::set_resolution(int ic)
{
	if (ic > Settings::resolutions.size() - 1)
	{
		ic = 0;
	}
	else if (ic < 0)
	{
		ic = Settings::resolutions.size() - 1;
	}

	Settings::current_res_index = ic;

	// Recreate window
	sf::RenderWindow* window = RenderMan::GetWindow();
	window->create(Settings::resolutions[Settings::current_res_index], "Black Dragon", gs::fullscreen ? sf::Style::Fullscreen : sf::Style::Default);

	//Maintain size on screen. Otherwise the window size would change
	sf::View view(sf::FloatRect(0, 0, 1920, 1080));
	window->setView(view);

	// Resolution text
	Settings::res_text->setString(std::to_string(RenderMan::GetWindow()->getSize().x)
		+ " X " + std::to_string(RenderMan::GetWindow()->getSize().y));

	// Set text origin and pos
	Settings::res_text->setOrigin(Settings::res_text->getScale().x / 2, Settings::res_text->getScale().y / 2);
	Settings::res_text->setPosition(1100, 650);

	std::cout << "Set res to " << Settings::resolutions[Settings::current_res_index].width <<
		Settings::resolutions[Settings::current_res_index].height << std::endl;
	std::cout << "i = " << Settings::current_res_index << std::endl;
}
void Settings::on_scene_inactive()
{
	std::cout << "Settings on_scene_inactive()" << std::endl;

	RenderMan::RemoveAllDrawObj();
	EventManager::clear_current_button();
}