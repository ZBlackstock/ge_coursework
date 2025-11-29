#include "message_box.hpp"
#include "Engine\game_system.hpp"
#include "Engine\RenderMan.h"
#include "Console.hpp"

std::shared_ptr<sf::Text> MsgBox::_message = std::make_shared<sf::Text>();

void MsgBox::init()
{
	MsgBox::_message->setFont(GameSystem::font_bold);
	MsgBox::_message->setColor(sf::Color::White);
	MsgBox::_message->setCharacterSize(25);
	MsgBox::_message->setOrigin(sf::Vector2f{ MsgBox::_message->getLocalBounds().width / 2, MsgBox::_message->getLocalBounds().height / 2 });
	MsgBox::_message->setPosition(GameSystem::screen_mid.x, GameSystem::screen_mid.y + 400);
	MsgBox::_message->setString("Fight!");

	RenderMan::createDrawable(MsgBox::_message, 4);
}

void MsgBox::set_text(std::string message)
{
	Console::print(message);
	MsgBox::_message->setString(message);
	MsgBox::_message->setOrigin(sf::Vector2f{ MsgBox::_message->getLocalBounds().width / 2, MsgBox::_message->getLocalBounds().height / 2 });
}