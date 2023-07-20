#include "pch.h"
#include "Editor.h"

void Editor::InitKeys()
{
	menuKeys["E-LEFT"] = supportedKeys->at("A");
	menuKeys["E-RGIHT"] = supportedKeys->at("D");
	menuKeys["E-UP"] = supportedKeys->at("W");
	menuKeys["E-DOWN"] = supportedKeys->at("S");
	menuKeys["MURDERIZE"] = supportedKeys->at("Escape");
	menuKeys["CHANGEG"] = supportedKeys->at("C");
}

Editor::Editor(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys):
	Scene(_target, _supportKeys)
{
	InitKeys();
	_rect.setPosition(sf::Vector2f(50, 50));
	_rect.setSize(sf::Vector2f(100, 100));
	_rect.setFillColor(sf::Color::Red);
}

Editor::~Editor()
{
}

void Editor::Update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("E-LEFT"))))
	{
		std::cout << "Izquierda-Editada" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("E-RIGHT"))))
	{
		std::cout << "Derecha-Editada" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("E-UP"))))
	{
		std::cout << "Arriba-Editada" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("E-DOWN"))))
	{
		std::cout << "Abajo-Editado" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("MURDERIZE"))))
	{
		EndState();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("CHANGEG"))))
	{
		States.state = 1;
	}
}

void Editor::Render(sf::RenderTarget* _target)
{
	_target->draw(_rect);
}
