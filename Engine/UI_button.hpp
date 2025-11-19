#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class Button
{
public:
	Button(std::string name_in_file, sf::Vector2f location, int sort_layer);
	~Button() = default;

	void set_above(std::shared_ptr<Button> button);
	void set_below(std::shared_ptr<Button> button);
	void update();
	void idle();
	void highlight();
	void select();

	virtual void on_select();
	bool is_selected();

	std::shared_ptr<Button> above = nullptr;
	std::shared_ptr<Button> below = nullptr;
private:

	bool _selected;
	sf::Vector2f _pos;
	std::string _name;
};