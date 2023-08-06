#include "pch.h"
#include "Editor.h"
#include "Menu.h"

void Editor::InitKeys()
{
	editorKeys["E-LEFT"] = supportedKeys->at("A");
	editorKeys["E-RIGHT"] = supportedKeys->at("D");
	editorKeys["E-UP"] = supportedKeys->at("W");
	editorKeys["E-DOWN"] = supportedKeys->at("S");
	editorKeys["MURDERIZE"] = supportedKeys->at("Escape");
	editorKeys["CHANGEG"] = supportedKeys->at("C");
	editorKeys["Pausation"] = supportedKeys->at("E");
}

Editor::Editor(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys, std::stack<Scene*>* _scenes):
	Scene(_target, _supportKeys, _scenes)
{
	InitKeys();
	_rect.setSize(sf::Vector2f(_window->getSize()));
	_rect.setFillColor(sf::Color::Magenta);
}

Editor::~Editor()
{
}

void Editor::Update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorKeys.at("E-LEFT"))))
	{
		std::cout << "Izquierda-Editada" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorKeys.at("E-RIGHT"))))
	{
		std::cout << "Derecha-Editada" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorKeys.at("E-UP"))))
	{
		std::cout << "Arriba-Editada" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorKeys.at("E-DOWN"))))
	{
		std::cout << "Abajo-Editado" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorKeys.at("MURDERIZE"))))
	{
		EndState();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorKeys.at("CHANGEG"))))
	{
		scene->push(new Menu(_window, supportedKeys, scene));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorKeys.at("Pausation"))))
	{
		std::cout << "You do nothing! You lose!" << "\n";
	}
}

void Editor::Render(sf::RenderTarget* _target)
{
	_target->draw(_rect);
}
