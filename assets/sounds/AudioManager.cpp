#include "Audio/AudioManager.h"
#include <iostream>

std::map<std::string, std::unique_ptr<sf::SoundBuffer>> AudioManager::_soundBuffers;
std::vector<std::unique_ptr<sf::Sound>> AudioManager::_soundPool;
std::unique_ptr<sf::Music> AudioManager::_music = nullptr;

float AudioManager::_soundVolume = 100.f;
float AudioManager::_musicVolume = 100.f;

AudioManager::FadeState AudioManager::_fadeState = AudioManager::FadeState::None;
float AudioManager::_fadeTimer = 0.f;
float AudioManager::_fadeDuration = 0.f;
float AudioManager::_fadeTargetVolume = 100.f;
float AudioManager::_fadeStartVolume = 0.f;

void AudioManager::loadSound(const std::string& name, const std::string& path) {
    if (_soundBuffers.find(name) != _soundBuffers.end())
        return;

    auto buffer = std::make_unique<sf::SoundBuffer>();
    if (!buffer->loadFromFile(path)) {
        std::cerr << "Failed to load sound: " << path << std::endl;
        return;
    }

    _soundBuffers[name] = std::move(buffer);
}

sf::Sound* AudioManager::getAvailableSound() {
    for (auto& s : _soundPool) {
        if (s->getStatus() == sf::Sound::Stopped)
            return s.get();
    }

    auto s = std::make_unique<sf::Sound>();
    s->setVolume(_soundVolume);
    _soundPool.push_back(std::move(s));
    return _soundPool.back().get();
}

void AudioManager::playSound(const std::string& name, float volume) {
    auto it = _soundBuffers.find(name);
    if (it == _soundBuffers.end()) {
        std::cerr << "Sound not loaded: " << name << std::endl;
        return;
    }

    sf::Sound* s = getAvailableSound();
    s->setBuffer(*it->second);
    s->setVolume(volume);
    s->play();
}

void AudioManager::playMusic(const std::string& path, bool loop, float volume) {
    _music = std::make_unique<sf::Music>();
    if (!_music->openFromFile(path)) {
        std::cerr << "Failed to open music: " << path << std::endl;
        return;
    }
    _music->setLoop(loop);
    _music->setVolume(volume);
    _music->play();
    _musicVolume = volume;
}

void AudioManager::stopMusic() {
    if (_music) _music->stop();
    _fadeState = FadeState::None;
}

void AudioManager::pauseMusic() {
    if (_music) _music->pause();
}

void AudioManager::resumeMusic() {
    if (_music && _music->getStatus() == sf::Music::Paused)
        _music->play();
}

void AudioManager::fadeInMusic(const std::string& path, float duration, bool loop, float targetVolume) {
    playMusic(path, loop, 0.f);
    _fadeState = FadeState::In;
    _fadeTimer = 0.f;
    _fadeDuration = duration;
    _fadeTargetVolume = targetVolume;
    _fadeStartVolume = 0.f;
}

void AudioManager::fadeOutMusic(float duration) {
    if (!_music) return;
    _fadeState = FadeState::Out;
    _fadeTimer = 0.f;
    _fadeDuration = duration;
    _fadeStartVolume = _music->getVolume();
}

void AudioManager::update(float dt) {
    if (_fadeState == FadeState::None || !_music)
        return;

    _fadeTimer += dt;
    float progress = std::min(_fadeTimer / _fadeDuration, 1.f);

    if (_fadeState == FadeState::In) {
        float newVol = _fadeStartVolume + (_fadeTargetVolume - _fadeStartVolume) * progress;
        _music->setVolume(newVol);
        if (progress >= 1.f) {
            _fadeState = FadeState::None;
            _musicVolume = _fadeTargetVolume;
        }
    }
    else if (_fadeState == FadeState::Out) {
        float newVol = _fadeStartVolume * (1.f - progress);
        _music->setVolume(newVol);
        if (progress >= 1.f) {
            _music->stop();
            _fadeState = FadeState::None;
            _musicVolume = 0.f;
        }
    }
}

void AudioManager::setSoundVolume(float volume) {
    _soundVolume = volume;
    for (auto& s : _soundPool)
        s->setVolume(volume);
}

void AudioManager::setMusicVolume(float volume) {
    _musicVolume = volume;
    if (_music)
        _music->setVolume(volume);
}

float AudioManager::getSoundVolume() { return _soundVolume; }
float AudioManager::getMusicVolume() { return _musicVolume; }
