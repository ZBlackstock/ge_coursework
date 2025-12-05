#include "healthbar.hpp"
#include "console.hpp"

using h = Healthbar;

h::Healthbar(sf::Vector2f size, sf::Vector2f pos, float max, sf::Color colour)
{
	// Set fill shape
	_fill = std::make_shared<sf::RectangleShape>();
	_fill->setSize(size);
	_fill->setPosition(pos);
	_fill->setOrigin({ _fill->getLocalBounds().width / 2, _fill->getLocalBounds().height / 2 });
	_fill->setFillColor(colour);

	// Set background (appears as white outline when full)
	_background = std::make_shared<sf::RectangleShape>();
	_background->setSize({ _fill->getSize().x + 10.f, _fill->getSize().y + 10.f });
	_background->setPosition(pos);
	_background->setOrigin({ _background->getLocalBounds().width / 2, _background->getLocalBounds().height / 2 });
	_background->setFillColor(sf::Color::White);

	// Render
	RenderMan::createDrawable(_background, 3);
	RenderMan::createDrawable(_fill, 4);

	*_max_width = _fill->getLocalBounds().width;
	*_max_value = max;
	*_value = *_max_value;
}

void h::set_healthbar_value(int value)
{
	// Check entity still has health left
	if (*_value > 0)
	{
		*_value = value;
		_fill->setSize({ (*_max_width / *_max_value) * *_value,_fill->getGlobalBounds().height });
	}
	else
	{
		// Avoids leaving a tiny sliver of health fill
		RenderMan::RemoveDrawObjByDrawable(_fill);
	}
}

float& h::get_healthbar_value()
{
	return *_value;
}