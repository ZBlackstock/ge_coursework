#include "UI_button.hpp"
#include "RenderMan.h"
#include <SFML/Graphics.hpp>
#include "game_system.h"
#include "event_man.hpp"
#include "UI_exit_to_mainmenu.hpp"
#include "SceneMan.hpp"
#include <iostream>
#include <string>

using b = Button;
using rm = RenderMan;
using gs = GameSystem;

b::Button(std::string name_in_file, sf::Vector2f location, int sort_layer)
{
	try
	{
		b::_name = name_in_file;
		b::_pos = location;
		b::_selected = false;
		RenderMan::create_sprite(_name + "_idle.png", _pos, sort_layer);
		RenderMan::create_sprite(_name + "_highlighted.png", { 10000,10000 }, sort_layer);
		RenderMan::create_sprite(_name + "_selected.png", { 10000,10000 }, sort_layer);
	}
	catch (int err)
	{
		std::cout << "Could not load button" << std::endl;
	}
}

void b::set_above(std::shared_ptr<Button> button)
{
	b::above = button;
}

void b::set_below(std::shared_ptr<Button> button)
{
	b::below = button;
}

void b::set_left(std::shared_ptr<Button> button)
{
	b::left = button;
}

void b::set_right(std::shared_ptr<Button> button)
{
	b::right = button;
}


// Needs to be called by event manager, which should have a list of buttons
void b::update()
{
	if (b::above != nullptr && b::above->is_selected() && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		b::highlight();
		b::above->idle();
	}
	else if (b::below != nullptr && b::below->is_selected() && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		b::highlight();
		b::below->idle();
	}
}

void b::set_pos(sf::Vector2f pos)
{
	b::_pos = pos;
	rm::set_sprite_pos(_name + "_idle.png", b::_pos);
}

void b::idle()
{
	rm::set_sprite_pos(_name + "_idle.png", b::_pos);
	rm::set_sprite_pos(_name + "_highlighted.png", { 10000,10000 });
}

void b::highlight()
{
	rm::set_sprite_pos(_name + "_highlighted.png", b::_pos);
	rm::set_sprite_pos(_name + "_idle.png", { 10000,10000 });
	rm::set_sprite_pos(_name + "_selected.png", { 10000,10000 });
}

void b::select()
{
	rm::set_sprite_pos(_name + "_selected.png", b::_pos);
	rm::set_sprite_pos(_name + "_highlighted.png", { 10000,10000 });
}

void b::on_select()
{
	std::cout << "Button Selected" << std::endl;
}

bool b::is_selected()
{
	return b::_selected;
}

std::string b::get_name()
{
	return b::_name;
}

void b::set_offscreen(bool offscreen)
{
	rm::set_sprite_pos(_name + "_highlighted.png", { 10000,10000 });
	rm::set_sprite_pos(_name + "_idle.png", !offscreen ? b::_pos : sf::Vector2f{ 10000,10000 });
	rm::set_sprite_pos(_name + "_selected.png", { 10000,10000 });
}

// ____________ Custom Buttons ____________________________

// Add custom button functionality for different button types

// - Quit game
void Button_Quit::on_select()
{
	RenderMan::GetWindow()->close();
}

// - Load Scene
void Button_LoadScene::on_select()
{
	SceneManager::set_active_scene(_scene);
}

void Button_LoadScene::set_scene_to_load(std::shared_ptr<Scene> scene)
{
	Button_LoadScene::_scene = scene;
}

void Button_Popup_No::on_select()
{
	ExitToMainMenu::set_active(false);
	EventManager::set_current_button(SceneManager::btn_fight_mid);
}

void Button_ToggleFullscreen::on_select()
{
	GameSystem::fullscreen = !GameSystem::fullscreen;

	sf::RenderWindow* window = RenderMan::GetWindow();
	window->create(sf::VideoMode(gs::screen_size.x, gs::screen_size.y), "Black Dragon", gs::fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
}