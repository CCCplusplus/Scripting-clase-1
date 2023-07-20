#include "pch.h"
#include "GameScene.h"

GameScene::GameScene(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys):
	Scene(_target,_supportKeys)
{
	InitKeys();
	_rect.setPosition(sf::Vector2f(50, 50));
	_rect.setSize(sf::Vector2f(100, 100));
	_rect.setFillColor(sf::Color::Blue);
}

GameScene::~GameScene()
{
}

void GameScene::InitKeys() 
{
	newKeys["MOVE_LEFT"] = supportedKeys->at("A");
	newKeys["MOVE_RIGHT"] = supportedKeys->at("D");
	newKeys["MOVE_UP"] = supportedKeys->at("W");
	newKeys["MOVE_DOWN"] = supportedKeys->at("S");
	newKeys["CLOSE"] = supportedKeys->at("Escape");
	newKeys["CHANGEM"] = supportedKeys->at("C");
}

void GameScene::Update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("MOVE_LEFT")))) 
	{
		std::cout << "move left" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("MOVE_RIGHT"))))
	{
		std::cout << "move right" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("MOVE_UP"))))
	{
		std::cout << "move up" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("MOVE_DOWN"))))
	{
		std::cout << "move down" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("CLOSE"))))
	{
		EndState();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("CHANGEM"))))
	{
		States.state = 2;
	}
}

void GameScene::Render(sf::RenderTarget* _target)
{
	_target->draw(_rect);
}
