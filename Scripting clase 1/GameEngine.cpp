#include "pch.h"
#include "GameEngine.h"
#include "GameScene.h"

void GameEngine::InitKeys()
{
	supportedKeys["A"] = 0;
	supportedKeys["D"] = 3;
	supportedKeys["Escape"] = 36;
	supportedKeys["S"] = 18;
	supportedKeys["W"] = 22;
	supportedKeys["C"] = 2;
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
	if (state == 1)
		game = new GameScene(_window, &supportedKeys);
	else if (state == 2)
		game = new GameScene(_window, &supportedKeys);
	else if (state == 3)
		game = new GameScene(_window, &supportedKeys);
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
	jugador.Update(_window);


	game->Update(deltaTime);
	if (game->GetQuit())
	{
		delete game;
	}
}

void GameEngine::Render()
{
	jugador.Render(_window);

	_window->clear();

	game->Render(_window);

	_window->display();
}

void GameEngine::UpdateDeltaTime()
{
	deltaTime = deltaClock.restart().asSeconds();
}
