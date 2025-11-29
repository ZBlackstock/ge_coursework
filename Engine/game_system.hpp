#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "ecm.hpp"

class Scene;//forward definition

class GameSystem{
public:
    static void start(unsigned int width, unsigned int height, 
                      const std::string& name, const float& time_step,
                      bool physics_enabled = false);
    static void reset();
    static sf::Vector2i screen_size;
    static sf::Vector2f screen_size_f; // float version, for sprite positioning
    static sf::Vector2f screen_mid; // float version, for sprite positioning
    static std::string sprites_path;
    static sf::Font font;
    static sf::Font font_bold;
    static bool fullscreen;
    static void assign_paths();
    static const std::shared_ptr<Entity>& make_entity();
    static std::vector<std::shared_ptr<Entity>>& get_entities() { return _entities.list; }

protected:
    static EntityManager _entities;


private:
    static void _update(const float &dt);
    static void _render();
};

