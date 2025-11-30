#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "Engine/RenderMan.h"


class Healthbar
{
public:
	Healthbar(sf::Vector2f size, sf::Vector2f pos, float max);
	void set_healthbar_value(float& value);

private:
	std::shared_ptr<float> _value = std::make_shared<float>();
	std::shared_ptr<float> _max_value = std::make_shared<float>();
	std::shared_ptr<sf::RectangleShape> _box = std::shared_ptr<sf::RectangleShape>();
};