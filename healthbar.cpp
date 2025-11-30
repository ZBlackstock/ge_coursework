#include "healthbar.hpp"

using h = Healthbar;

h::Healthbar(float& max)
{
	*_max_value = max;
	RenderMan::createDrawable(sf::RectangleShape(_max_value), 3)
}

void h::init()
{
}

void h::set_healthbar_value(float& value)
{
	*_value = value;
	
}