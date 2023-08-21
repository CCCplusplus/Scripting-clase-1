#include "pch.h"
#include "GameEngine.h"
#include "GameScene.h"
#include "Menu.h"

void GameEngine::InitKeys()
{
	supportedKeys["A"] = 0;
	supportedKeys["D"] = 3;
	supportedKeys["Escape"] = 36;
	supportedKeys["S"] = 18;
	supportedKeys["W"] = 22;
	supportedKeys["C"] = 2;
	supportedKeys["E"] = 4;
}

void GameEngine::InitWindow()
{
	_window = nullptr;
	_video = sf::VideoMode::getDesktopMode();
	header = "Window";
	fullscreen = false;

	if (fullscreen)
		_window = new sf::RenderWindow(_video, header);

	else
	{
		_window = new sf::RenderWindow(_video, header, sf::Style::Titlebar | sf::Style::Close);
	}

	_window->setFramerateLimit(60);
}

void GameEngine::InitScene()
{
	scenes.push(new Menu(_window, &supportedKeys, &scenes, &luaScripts));
}


GameEngine::GameEngine()
{
	this->InitWindow();
	this->InitKeys();
	this->InitScene();
	
}

GameEngine::~GameEngine()
{
}

const bool GameEngine::GetWindowOpen()
{
	return _window->isOpen();
}

void GameEngine::Update()
{
	//jugador.Update(_window);

	if (!scenes.empty()) 
	{
		scenes.top()->Update(deltaTime);
		if (scenes.top()->GetQuit()) 
		{
			scenes.top()->EndState();
			delete scenes.top();
			scenes.pop();

			delete luaScripts.top();
			luaScripts.pop();
		}
	}
	else 
	{
		_window->close();
	}
}

void GameEngine::Render()
{

	_window->clear();
	//jugador.Render(_window);

	if (!scenes.empty()) {
		scenes.top()->Render(_window);
	}

	_window->display();
}

void GameEngine::UpdateDeltaTime()
{
	deltaTime = deltaClock.restart().asSeconds();
}
