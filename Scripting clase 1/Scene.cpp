#include "pch.h"
#include "Scene.h"

Scene::Scene(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys)
{
	_window = _target;
	supportedKeys = _supportKeys;
	
	quit = false;
}

Scene::~Scene()
{
}

void Scene::EndState()
{
	quit = true;
}


void Scene::UpdateMousePos()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition();
	mousePosView = _window->mapPixelToCoords(mousePosWindow);
}

const bool Scene::GetQuit()
{
	return quit;
}
