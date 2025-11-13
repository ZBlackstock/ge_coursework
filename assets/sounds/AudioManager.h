#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>

class AudioManager {
public:
    static void loadSound(const std::string& name, const std::string& path);
    static void playSound(const std::string& name, float volume = 100.f);

    static void playMusic(const std::string& path, bool loop = true, float volume = 100.f);
    static void stopMusic();
    static void pauseMusic();
    static void resumeMusic();

    // Fade controls
    static void fadeInMusic(const std::string& path, float duration, bool loop = true, float targetVolume = 100.f);
    static void fadeOutMusic(float duration);

    // Call once per frame with delta time in seconds
    static void update(float dt);

    static void setSoundVolume(float volume);
    static void setMusicVolume(float volume);
    static float getSoundVolume();
    static float getMusicVolume();

private:
    static std::map<std::string, std::unique_ptr<sf::SoundBuffer>> _soundBuffers;
    static std::vector<std::unique_ptr<sf::Sound>> _soundPool;
    static std::unique_ptr<sf::Music> _music;

    static float _soundVolume;
    static float _musicVolume;

    enum class FadeState { None, In, Out };
    static FadeState _fadeState;
    static float _fadeTimer;
    static float _fadeDuration;
    static float _fadeTargetVolume;
    static float _fadeStartVolume;

    static sf::Sound* getAvailableSound();
};
