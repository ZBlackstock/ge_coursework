#include "message_box.hpp"
#include "Engine\game_system.hpp"
#include "Engine\RenderMan.h"

void MessageBox::init()
{
	MessageBox::_message->setPosition(GameSystem::screen_mid.x, GameSystem::screen_mid.y + 400);
	MessageBox::_message->setFont(GameSystem::font_bold);
	MessageBox::_message->setColor(sf::Color::White);
	MessageBox::_message->setCharacterSize(50);

	RenderMan::createDrawable(MessageBox::_message, 5);
}

void MessageBox::set_text(std::string message)
{
	MessageBox::_message->setString(message);
}