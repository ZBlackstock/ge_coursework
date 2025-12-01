#include <SFML/Audio.hpp>
#include "AudioManager.h"
#include <iostream>

// ======================
// Static member storage
// ======================
// These are the actual definitions of the static members declared in the header.
// They must exist in exactly one .cpp file.
std::vector<sf::SoundBuffer> AudioManager::buffers;
std::map<std::shared_ptr<sf::Sound>, std::string> AudioManager::activeSounds;
std::unique_ptr<sf::Music> AudioManager::currentSong = nullptr;



// ============================================================================
// Adds a sound effect by name, loads its buffer, and stores a playable sf::Sound
// ============================================================================
// - The sound buffer is stored inside `buffers` so it stays alive for the
//   lifetime of the program (SFML requires buffer to outlive sf::Sound).
// - A shared_ptr<sf::Sound> is created and stored in `activeSounds`.
// - No memory leaks: std::vector + smart pointers handle cleanup automatically.
// ============================================================================
void AudioManager::addSounds(const std::string& S_name)
{
	// Create a new buffer in the vector
	buffers.emplace_back();
	sf::SoundBuffer& buffer = buffers.back();

	// Load file into the buffer
	if (!buffer.loadFromFile("../../../../res/sounds/" + S_name + ".wav"))
	{
		std::cerr << "Failed to load " << S_name << "\n";

		// Remove the last buffer to avoid storing an invalid buffer
		buffers.pop_back();
		return;
	}

	// Create a new sound and link it to the buffer
	auto sound = std::make_shared<sf::Sound>();
	sound->setBuffer(buffer);
	sound->setVolume(100.f);

	// Store the sound so we can play it later
	activeSounds.emplace(sound, S_name);
}



// ============================================================================
// Plays all loaded sound effects
// ============================================================================
// - Loops through activeSounds and plays each one.
// - No copying occurs because we iterate by reference.
// ============================================================================
void AudioManager::playSounds()
{
	int ic = 0;
	for (auto it = activeSounds.begin(); it != activeSounds.end() && ic < activeSounds.size(); ++it, ++ic)
	{
		std::cout << "Playing sound\n";
		it->first->play();
	}
}

// Play sound by name
void AudioManager::playSound(std::string name)
{
	int ic = 0;
	for (auto it = activeSounds.begin(); it != activeSounds.end() && ic < activeSounds.size(); ++it, ++ic)
	{
		if (it->second == name)
		{
			it->first->play();
			break;
		}
	}
}


// ============================================================================
// Loads and plays background music
// ============================================================================
// - Uses std::unique_ptr<sf::Music> to ensure automatic cleanup.
// - Only one music track can be active at once.
// - sf::Music streams from file, so it must stay alive while playing.
// ============================================================================
void AudioManager::addMusic(const std::string& M_name)
{
	// Create a new music object
	currentSong = std::make_unique<sf::Music>();

	// Attempt to load the file
	if (!currentSong->openFromFile("../../../../res/music/" + M_name + ".ogg"))
	{
		std::cerr << "Failed to load music\n";
		return;
	}

	// Enable looping and start playback
	currentSong->setLoop(true);
	currentSong->play();
}



// ============================================================================
// Clears all loaded sound effects
// ============================================================================
// - Frees all sf::Sound and sf::SoundBuffer instances by clearing vectors.
// - No leaks because smart pointers and vectors automatically release memory.
// ============================================================================
void AudioManager::clearSounds()
{
	activeSounds.clear();
	buffers.clear();
}
