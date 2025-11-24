#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "SceneMan.hpp"

class Button
{
public:
	Button(std::string name_in_file, sf::Vector2f location, int sort_layer);
	~Button() = default;

	void set_above(std::shared_ptr<Button> button);
	void set_below(std::shared_ptr<Button> button);
	void set_left(std::shared_ptr<Button> button);
	void set_right(std::shared_ptr<Button> button);
	void update();
	void idle();
	void highlight();
	void select();

	virtual void on_select();
	bool is_selected();
	std::string get_name();

	std::shared_ptr<Button> above = nullptr;
	std::shared_ptr<Button> below = nullptr;
	std::shared_ptr<Button> left = nullptr;
	std::shared_ptr<Button> right = nullptr;
private:

	bool _selected;
	sf::Vector2f _pos;
	std::string _name;
};

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