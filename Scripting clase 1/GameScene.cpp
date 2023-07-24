#include "pch.h"
#include "GameScene.h"
#include "Editor.h"

GameScene::GameScene(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys, std::stack<Scene*>* _scenes):
	Scene(_target,_supportKeys,_scenes)
{
	InitKeys();
	InitPlayer();
	/*_rect.setSize(sf::Vector2f(_window->getSize()));
	_rect.setFillColor(sf::Color::Blue);*/
}

GameScene::~GameScene()
{
	delete _player;
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

void GameScene::InitPlayer()
{
	_player = new Player(10, 10);
}

void GameScene::Update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("MOVE_LEFT")))) 
	{
		_player->Move(-1, 0, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("MOVE_RIGHT"))))
	{
		_player->Move(1, 0, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("MOVE_UP"))))
	{
		_player->Move(0, -1, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("MOVE_DOWN"))))
	{
		_player->Move(0, 1, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("CLOSE"))))
	{
		EndState();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("CHANGEM"))))
	{
		scene->push(new Editor(_window, supportedKeys, scene));
	}
}

void GameScene::Render(sf::RenderTarget* _target)
{
	/*_target->draw(_rect);*/

	_player->Render(_target);
}
