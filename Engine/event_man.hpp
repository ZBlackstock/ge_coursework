#pragma once
#include<memory>
#include<SFML/Graphics.hpp>


class Button
{
public:
	Button(std::string name_in_file, sf::Vector2f location, int sort_layer);
	~Button() = default;

	void set_offscreen(bool offscreen);


	void set_above(std::shared_ptr<Button> button);
	void set_below(std::shared_ptr<Button> button);
	void set_left(std::shared_ptr<Button> button);
	void set_right(std::shared_ptr<Button> button);
	void update();
	void idle();
	void highlight();
	void select();
	void disable();

	virtual void on_select();
	void set_pos(sf::Vector2f pos);
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

class EventManager
{
public:
	static std::shared_ptr<Button>  get_current_button();
	static void set_current_button(std::shared_ptr<Button>  button);
	static void clear_current_button();
	static void update(const float& dt);

private:
	static std::shared_ptr<Button> _currentButton;
	static void button_navigate_detect();
};