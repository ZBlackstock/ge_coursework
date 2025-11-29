#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>

// ============================================================================
// AudioManager
// A static helper class for loading and playing sound effects and music.
// Manages audio resources globally with safe, automatic memory handling.
// ============================================================================
class AudioManager
{
public:
    // Play all loaded sound effects.
    static void playSounds();

    // play sound by name
    static void playSound(std::string name);

    // Load a .wav sound and store it for playback.
    static void addSounds(const std::string& S_name);

    // Load and play looping background music (.ogg).
    static void addMusic(const std::string& M_name);

    // Free all stored sound effects (buffers + sounds).
    static void clearSounds();

private:
    // Persistent storage for sound buffers (must outlive sounds).
    static std::vector<sf::SoundBuffer> buffers;

    // Active sound objects referencing the buffers.
    static std::map<std::shared_ptr<sf::Sound>, std::string> activeSounds;

    // Currently playing background music.
    static std::unique_ptr<sf::Music> currentSong;
};
