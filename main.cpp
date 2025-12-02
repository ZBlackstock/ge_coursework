#include "SceneMan.hpp"
#include "Engine\game_system.hpp"

using gs = GameSystem;

sf::Vector2i gs::screen_size = sf::Vector2i{ 1920,1080 };
sf::Vector2f gs::screen_size_f = static_cast<sf::Vector2f>(gs::screen_size);
sf::Vector2f gs::screen_mid = sf::Vector2f{ gs::screen_size_f.x / 2, (gs::screen_size_f.y / 2) };
std::string GameSystem::sprites_path = "../../../../res/sprites/";
sf::Font gs::font;
sf::Font gs::font_bold;
bool gs::fullscreen = true;

int main()
{
	SceneManager::init();

	//resolutions store valid resolutions for device. Set it to the best one (the first)
	sf::VideoMode start_res = Settings::resolutions[0];
	gs::start(start_res.width, start_res.height, "Black Dragon", 0.017f, false);

	gs::screen_size = sf::Vector2i{ static_cast<int>(start_res.width),  static_cast<int>(start_res.height)};
	gs::screen_size_f = sf::Vector2f{ static_cast<float>(start_res.width), static_cast<float>(start_res.height) };
	gs::screen_mid = sf::Vector2f{ gs::screen_size_f.x / 2, gs::screen_size_f.y / 2 };
	return 0;
}

