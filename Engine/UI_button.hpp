#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
	Button(Button above, Button Below);
	~Button() = default;

	// Strings, because they are grabbed as sprites via filenames
	std::string idle;
	std::string highlighted;
	std::string selected;
	std::string disabled;

private:
	Button _above;
	Button _below;
};