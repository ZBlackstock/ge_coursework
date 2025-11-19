#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
	Button(std::string name_in_file, Button above, Button Below);
	~Button() = default;

private:
	Button _above;
	Button _below;

	// Strings, because they are grabbed as sprites via filenames
	// Private, because they should all be under same name
	// Example: name = "play". These should be named in file as "play_idle", "play_highlighted" etc.
	std::string idle;
	std::string highlighted;
	std::string selected;
	std::string disabled;
};