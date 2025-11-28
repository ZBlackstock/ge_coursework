#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "SceneMan.hpp"
#include "event_man.hpp"
#include "consumable_man.hpp"


class Consumable;
// ____________ Custom Buttons ____________________________

class Button_Quit : public Button
{
public:
	virtual void on_select();
	Button_Quit(std::string name_in_file, sf::Vector2f location, int sort_layer) :
		Button(name_in_file, location, sort_layer) {
	}
};

class Button_LoadScene : public Button
{
public:
	virtual void on_select();
	Button_LoadScene(std::string name_in_file, sf::Vector2f location, int sort_layer) :
		Button(name_in_file, location, sort_layer) {
	}
	void set_scene_to_load(std::shared_ptr<Scene> scene);

private:
	std::shared_ptr<Scene> _scene = std::shared_ptr<Scene>();
};

class Button_Popup_No : public Button
{
public:
	virtual void on_select();
	Button_Popup_No(std::string name_in_file, sf::Vector2f location, int sort_layer) :
		Button(name_in_file, location, sort_layer) {
	}
};

class Button_ToggleFullscreen : public Button
{
public:
	virtual void on_select();
	Button_ToggleFullscreen(std::string name_in_file, sf::Vector2f location, int sort_layer) :
		Button(name_in_file, location, sort_layer) {
	}
};

class Button_Consumable : public Button
{
public:
	virtual void on_select();
	Button_Consumable(std::string name_in_file, sf::Vector2f location, int sort_layer) :
		Button(name_in_file, location, sort_layer) {
	}
	void set_consumable(std::shared_ptr<Consumable> cns);

private:
	std::shared_ptr<Consumable> _consumable = nullptr;
};

class Button_SetResolution : public Button
{
public:
	virtual void on_select();
	Button_SetResolution(std::string name_in_file, sf::Vector2f location, int sort_layer) :
		Button(name_in_file, location, sort_layer) {
	}
	void set_change(int change);

private:
	//The number the res changes by
	int _change = 0;
};

class Button_KeyBind : public Button
{
public:
	virtual void on_select();
	Button_KeyBind(std::string name_in_file, sf::Vector2f location, int sort_layer) :
		Button(name_in_file, location, sort_layer) {
	}
	void set_input(sf::Keyboard::Key key);
	std::shared_ptr< sf::Text> text = std::make_shared<sf::Text>();
	sf::Vector2f txt_pos;
	void text_init();
	void set_text();
	void clear_text();

private:
	// Target key to change
	sf::Keyboard::Key _target_input;
};