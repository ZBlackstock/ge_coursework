#include <SFML/Audio.hpp>
#include "AudioManager.h"
#include <iostream>

/*void AudioManager::initialise() {
    //activeSounds = new vector
}*/

void AudioManager::playSounds()
{
    for ( std::shared_ptr<sf::Sound> sound : activeSounds) {
        std::cout << "SOUNDS ARE PLAYING";
        sound->play();
    }
}

void AudioManager::addSounds(const std::string& name)
{
    buffers.emplace_back();
    sf::SoundBuffer& buffer = buffers.back();
    //sf::SoundBuffer buffer;
    buffer.loadFromFile("../../../../assets/" + name + ".wav");
    sf::Sound anotherSound(buffer);
    anotherSound.setVolume(100.f);
    //anotherSound.
    std::shared_ptr<sf::Sound> soundy = std::make_shared<sf::Sound>();
    soundy->setBuffer(buffer);
    soundy->setVolume(100.f);
    std::cout << "this should work";
    //soundy.
    activeSounds.push_back(soundy);
}