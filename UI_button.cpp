#include "UI_button.hpp"
#include "RenderMan.h"
#include <SFML/Graphics.hpp>
#include "game_system.hpp"
#include "event_man.hpp"
#include "UI_exit_to_mainmenu.hpp"
#include "SceneMan.hpp"
#include "input_man.hpp"
#include "Console.hpp"
#include <iostream>
#include <string>
#include <algorithm>

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

// For Disabling entire HUD elements
void b::set_all_sprites_pos(sf::Vector2f pos)
{
	b::_pos = pos;
	rm::set_sprite_pos(_name + "_idle.png", b::_pos);
	rm::set_sprite_pos(_name + "_highlighted.png", b::_pos);
	rm::set_sprite_pos(_name + "_selected.png", b::_pos);
}

void b::idle()
{
	rm::set_sprite_pos(_name + "_idle.png", b::_pos);
	rm::set_sprite_pos(_name + "_highlighted.png", { 10000,10000 });
	on_idle();
}

void b::highlight()
{
	rm::set_sprite_pos(_name + "_highlighted.png", b::_pos);
	rm::set_sprite_pos(_name + "_idle.png", { 10000,10000 });
	rm::set_sprite_pos(_name + "_selected.png", { 10000,10000 });
	on_highlight();
}

void b::submit()
{
	rm::set_sprite_pos(_name + "_selected.png", b::_pos);
	rm::set_sprite_pos(_name + "_idle.png", { 10000,10000 });
	rm::set_sprite_pos(_name + "_highlighted.png", { 10000,10000 });
}

void b::disable()
{
	rm::set_sprite_pos(_name + "_selected.png", b::_pos);
	rm::set_sprite_pos(_name + "_idle.png", { 10000,10000 });
	rm::set_sprite_pos(_name + "_highlighted.png", { 10000,10000 });

	if (b::above)
	{
		b::below->set_above(b::above);
	}
	if (b::below)
	{
		b::above->set_below(b::below);
	}
}

void b::on_select()
{
	std::cout << "Button Selected" << std::endl;
}

void b::on_highlight() {}
void b::on_idle() {}

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
	if (_scene != nullptr)
	{
		SceneManager::set_active_scene(_scene);
	}
}

void Button_LoadScene::set_scene_to_load(std::shared_ptr<Scene> scene)
{
	Button_LoadScene::_scene = scene;
}

void Button_Popup_No::on_select()
{
	ExitToMainMenu::set_active(false);
}

void Button_ToggleFullscreen::on_select()
{
	GameSystem::fullscreen = !GameSystem::fullscreen;

	sf::RenderWindow* window = RenderMan::GetWindow();
	window->create(sf::VideoMode(gs::screen_size.x, gs::screen_size.y), "Black Dragon", gs::fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
}

void Button_Item::on_idle()
{
	Console::print("on_idle() " + Button_Item::_item->get_name());
	Button_Item::_item->display_description(false);
}

void Button_Item::on_highlight()
{
	Console::print("on_highlight() " + Button_Item::_item->get_name());
	Button_Item::_item->display_description(true);
}

void Button_Item::on_select()
{
	Console::print("on_select() " + Button_Item::_item->get_name());
	Button_Item::_item->on_use();
	Button_Item::_item->display_description(false);
}

void Button_Item::set_consumable(std::shared_ptr<Item> i)
{
	Button_Item::_item = i;
}

void Button_Item::set_user(std::shared_ptr<Entity> user, std::shared_ptr<Entity> opponent)
{
	Button_Item::user = user;
	Button_Item::opponent = opponent;
}

void Button_SetResolution::set_change(int change)
{
	Button_SetResolution::_change = change;
}

void Button_SetResolution::on_select()
{
	Settings::set_resolution(_change);
}

bool Button_KeyBind::assigning_key = false;
void Button_KeyBind::set_input(sf::Keyboard::Key key)
{
	Button_KeyBind::_target_input = key;
}

void Button_KeyBind::on_select()
{
	if (!Button_KeyBind::assigning_key)
	{
		Button_KeyBind::assigning_key = true;
		Button_KeyBind::clear_text();

		RenderMan::RenderWindow();

		bool key_assigned = false;
		while (!key_assigned)
		{
			sf::Event event;
			while (RenderMan::GetWindow()->pollEvent(event))
			{
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code != sf::Keyboard::Escape && !InputManager::is_key_in_use(event.key.code)) // Check not already in use
					{
						if (Button_KeyBind::_target_input == InputManager::submit)
						{
							InputManager::assign_submit(event.key.code);
						}
						else if (Button_KeyBind::_target_input == InputManager::up)
						{
							InputManager::assign_up(event.key.code);
						}
						else if (Button_KeyBind::_target_input == InputManager::down)
						{
							InputManager::assign_down(event.key.code);
						}
						else if (Button_KeyBind::_target_input == InputManager::left)
						{
							InputManager::assign_left(event.key.code);
						}
						else if (Button_KeyBind::_target_input == InputManager::right)
						{
							InputManager::assign_right(event.key.code);
						}

						Button_KeyBind::_target_input = event.key.code;
						key_assigned = true;
					}
					else
					{
						if (event.key.code == sf::Keyboard::Escape)
						{
							Button_KeyBind::text->setString("Cannot bind this key!");
						}
						else if (InputManager::is_key_in_use(event.key.code))
						{
							Button_KeyBind::text->setString("Already in use!");
						}

						//Otherwise text doesnt show
						RenderMan::RenderWindowClear();
						RenderMan::RenderWindow();
					}
				}
			}
		}
		Button_KeyBind::set_text();
		Button_KeyBind::assigning_key = false;
		sf::sleep(sf::seconds(0.5)); //Stops funky behaviour with already assigned keys
	}
}

void Button_KeyBind::text_init()
{
	Button_KeyBind::text->setPosition(Button_KeyBind::txt_pos);
	Button_KeyBind::text->setFont(GameSystem::font_bold);
	Button_KeyBind::text->setCharacterSize(40);
	Button_KeyBind::text->setColor(sf::Color::White);
	Button_KeyBind::set_text();

	RenderMan::createDrawable(Button_KeyBind::text, 2);
}

void Button_KeyBind::set_text()
{
	Button_KeyBind::text->setString(InputManager::key_to_string(Button_KeyBind::_target_input));
}

void Button_KeyBind::clear_text()
{
	Button_KeyBind::text->setString("Assign Key");
}

void Button_ResetKeyBinds::on_select()
{
	InputManager::reset_key_binds();
}