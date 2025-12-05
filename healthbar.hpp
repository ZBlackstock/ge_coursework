#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "Engine/RenderMan.h"


class Healthbar
{
public:
	Healthbar(sf::Vector2f size, sf::Vector2f pos, float max, sf::Color colour);
	void set_healthbar_value(int value);
	float& get_healthbar_value();

private:
	std::shared_ptr<float> _value = std::make_shared<float>();
	std::shared_ptr<float> _max_value = std::make_shared<float>();
	std::shared_ptr<float> _max_width = std::make_shared<float>();
	std::shared_ptr<sf::RectangleShape> _fill = std::shared_ptr<sf::RectangleShape>();
	std::shared_ptr<sf::RectangleShape> _background = std::shared_ptr<sf::RectangleShape>();

};