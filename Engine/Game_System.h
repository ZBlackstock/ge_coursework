#pragma once

class GameSystem
{
public:
    static void start(unsigned int width, unsigned int height,
        const std::string& name, const float& time_step);

private:
    static void _init();
    static void _update(const float& dt);
    static void _render();
    static std::shared_ptr<Scene> _active_scene;

};
