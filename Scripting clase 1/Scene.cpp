#include "pch.h"
#include "Scene.h"



Scene::Scene(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys, std::stack<Scene*>* _scenes, std::stack<LuaReader*>* _luaScripts)
{
	this->_window = _target;
	this->supportedKeys = _supportKeys;
	this->scene = _scenes;
	this->luaScripts = _luaScripts;

	quit = false;
}

Scene::~Scene()
{
}

void Scene::EndState()
{
	quit = true;
}



void Scene::InitLua()
{
}

void Scene::ExecuteLuaUpdate()
{
	_luaReader->Update();
}

void Scene::ExecuteLuaRender()
{
	_luaReader->Render();
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
