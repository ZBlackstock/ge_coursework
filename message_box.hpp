#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class MessageBox
{
public:
	static void init();
	static void set_text(std::string message);

private:
	static std::shared_ptr<std::string> message;

};