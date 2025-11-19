#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
	Button(std::string name_in_file, Button above, Button Below, sf::Vector2f location, int sort_layer);
	~Button() = default;

private:
	Button _above;
	Button _below;
};