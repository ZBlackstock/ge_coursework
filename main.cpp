#include "SceneMan.hpp"
#include "Engine\game_system.hpp"

using gs = GameSystem;

sf::Vector2i gs::screen_size = sf::Vector2i{ 1920,1080 };
sf::Vector2f gs::screen_size_f = static_cast<sf::Vector2f>(gs::screen_size);
sf::Vector2f gs::screen_mid = sf::Vector2f{ gs::screen_size_f.x / 2, (gs::screen_size_f.y / 2)};
std::string GameSystem::sprites_path = "../../../../res/sprites/";
sf::Font gs::font;
sf::Font gs::font_bold;
bool gs::fullscreen = true;

int main() 
{
	SceneManager::init();
	gs::start(gs::screen_size.x, gs::screen_size.y, "Black Dragon", 0.017f, false);
	return 0;
}

