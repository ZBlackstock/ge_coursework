#include <SFML/Graphics.hpp>
#include "assets/sounds/AudioManager.h"
#include <iostream>


int main() {
    // Create a window (just to keep SFML running)
    sf::RenderWindow window(sf::VideoMode(800, 600), "AudioManager Example");
    window.setFramerateLimit(60);

    // Clock for delta time (used by AudioManager::update)
    sf::Clock clock;

    // --- Load assets ---
    // Make sure these files exist in your project:
    // assets/sounds/shoot.wav
    // assets/sounds/explosion.wav
    // assets/music/background.ogg
    AudioManager::loadSound("shoot", "assets/sounds/shoot.wav");
    AudioManager::loadSound("explosion", "assets/sounds/explosion.wav");

    // Start background music with a fade-in
    AudioManager::fadeInMusic("assets/music/background.ogg", 2.0f, true, 70.f);

    // --- Simple UI text (optional) ---
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/RobotoMono-Regular.ttf")) {
        // Just ignore if you don't have a font
        std::cerr << "Could not load font\n";
    }

    sf::Text helpText(
        "Press SPACE to shoot\n"
        "Press E for explosion\n"
        "Press F to fade out music\n"
        "Press R to fade in music\n"
        "Press ESC to quit",
        font, 22);
    helpText.setPosition(20.f, 20.f);
    helpText.setFillColor(sf::Color::White);

    // --- Main
