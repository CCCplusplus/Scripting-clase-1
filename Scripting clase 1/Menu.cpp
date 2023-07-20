#include "pch.h"
#include "Menu.h"

void Menu::InitKeys()
{
	menuKeys["ONETOTHELEFT"] = supportedKeys->at("A");
	menuKeys["ONETOTHERIGHT"] = supportedKeys->at("D");
	menuKeys["ONEUP"] = supportedKeys->at("W");
	menuKeys["ONEDOWN"] = supportedKeys->at("S");
	menuKeys["DIE"] = supportedKeys->at("Escape");
	menuKeys["CHANGEE"] = supportedKeys->at("C");
}

Menu::Menu(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys): 
	Scene(_target, _supportKeys)
{
	InitKeys();
	_rect.setPosition(sf::Vector2f(50, 50));
	_rect.setSize(sf::Vector2f(100, 100));
	_rect.setFillColor(sf::Color::Green);
}

Menu::~Menu()
{
}

void Menu::Update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("ONETOTHELEFT"))))
	{
		std::cout << "movidita a la izquierda" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("ONETOTHERIGHT"))))
	{
		std::cout << "movidita a la derecha" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("ONEUP"))))
	{
		std::cout << "movidita arriba" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("ONEDOWN"))))
	{
		std::cout << "movidita abajo" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("DIE"))))
	{
		EndState();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("CHANGEE"))))
	{
		States.state = 3;
	}
}

void Menu::Render(sf::RenderTarget* _target)
{
	_target->draw(_rect);
}
