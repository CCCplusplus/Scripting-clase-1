#include "pch.h"
#include "Menu.h"
#include "GameScene.h"

void Menu::InitFont()
{
	_font.loadFromFile("OptimusPrinceps.ttf");
}

void Menu::InitButton()
{
	button = new GUI::Button(100, 100, 350, 250, &_font,
		"New Button", 50, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color::Red, sf::Color::Blue, sf::Color::Green);
}

void Menu::InitKeys()
{
	menuKeys["ONETOTHELEFT"] = supportedKeys->at("A");
	menuKeys["ONETOTHERIGHT"] = supportedKeys->at("D");
	menuKeys["ONEUP"] = supportedKeys->at("W");
	menuKeys["ONEDOWN"] = supportedKeys->at("S");
	menuKeys["DIE"] = supportedKeys->at("Escape");
	menuKeys["CHANGEE"] = supportedKeys->at("C");
}

Menu::Menu(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys, std::stack<Scene*>* _scenes): 
	Scene(_target, _supportKeys,_scenes)
{
	InitKeys();
	InitFont();
	InitButton();
	_rect.setSize(sf::Vector2f(_window->getSize()));
	_rect.setFillColor(sf::Color::Green);
}

Menu::~Menu()
{
}

void Menu::Update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("ONETOTHELEFT"))))
	{
		std::cout << "movidita a la izquierda" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("ONETOTHERIGHT"))))
	{
		std::cout << "movidita a la derecha" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("ONEUP"))))
	{
		std::cout << "movidita arriba" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("ONEDOWN"))))
	{
		std::cout << "movidita abajo" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("DIE"))))
	{
		EndState();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("CHANGEE"))))
	{
		scene->push(new GameScene(_window, supportedKeys, scene));
	}
}

void Menu::Render(sf::RenderTarget* _target)
{
	_target->draw(_rect);
	button->Render(_target);
}
