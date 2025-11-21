#include <SFML/Graphics.hpp>
#include "Engine\RenderMan.h"
#include "Engine\AudioManager.h"

int main() {

    // Create the main application window (1000x1000)
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML Test");

    // Rendering and audio managers
    RenderMan renderer;
    AudioManager audioMan;

    // Tell RenderMan which window to draw into
    renderer.SetWindow(&window);

    // --------------------------------------------------------------------
    // AUDIO: Load and play a sound effect
    // --------------------------------------------------------------------
    // Loads "shoot.wav" from assets and stores it in AudioManager's buffer list.
    // Creates a sound object that can be played at any time.
    audioMan.addSounds("shoot");

    // Immediately plays all loaded sound effects (currently just "shoot")
    audioMan.playSounds();


    // --------------------------------------------------------------------
    // GRAPHICS: Create two simple shapes to draw
    // --------------------------------------------------------------------

    // Green circle with radius 200 positioned at (0, 0)
    auto circle = std::make_shared<sf::CircleShape>(200.f);
    circle->setFillColor(sf::Color::Green);
    circle->setPosition(0, 0);

    // Yellow rectangle 300x300 positioned at the top-right initially
    auto pain = std::make_shared<sf::RectangleShape>(sf::Vector2f(300.f, 300.f));
    pain->setFillColor(sf::Color::Yellow);
    pain->setPosition(1000, 0);

    // Add shapes to RenderMan with layer indices
    renderer.createDrawable(circle, 1);  // Drawn on layer 1
    renderer.createDrawable(pain, 0);    // Drawn on layer 0

    // Remove the rectangle from RenderMan (no longer drawn)
    renderer.RemoveDrawObjByDrawable(pain);


    // --------------------------------------------------------------------
    // AUDIO: Start background music
    // --------------------------------------------------------------------
    // Loads "background.ogg" and begins looping playback.
    // Music streams from file and continues until stopped or program ends.
    audioMan.addMusic("background");


    // --------------------------------------------------------------------
    // Main Game Loop
    // --------------------------------------------------------------------
    while (window.isOpen()) {

        // Clear the window (RenderMan handles clear color)
        renderer.RenderWindowClear();
        sf::Event event;

        // Move the rectangle left over time (even though it's not rendered)
        pain->setPosition(pain->getPosition().x - 1, 50);

        // Handle window events (e.g., close button)
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        // Draw all currently registered drawables
        renderer.RenderWindow();
    }

    return 0;
}
