#include "healthbar.hpp"

using h = Healthbar;

h::Healthbar(sf::Vector2f size, sf::Vector2f pos, float max)
{
	_box = std::make_shared<sf::RectangleShape>();
	_box->setSize(size);
	_box->setPosition(pos);
	RenderMan::createDrawable(_box, 3);

	*_max_value = max;
}

void h::set_healthbar_value(float& value)
{
	*_value = value;
}