#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AudioManager 
{
public:
	//void initialise();
	void playSounds();
	void addSounds(const std::string& name);

private:
	std::vector<sf::SoundBuffer> buffers;
	std::vector<std::shared_ptr<sf::Sound>> activeSounds;
	std::unique_ptr<sf::Music> currentSong;
};