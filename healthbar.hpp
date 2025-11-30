#pragma once
#include <memory>


class Healthbar
{
public:
	void init();
	void set_healthbar_value(float& value);

private:
	std::make_shared<float> _value = std::make_shared<float>();
};