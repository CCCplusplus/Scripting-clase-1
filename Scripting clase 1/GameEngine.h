#pragma once
#include "Scene.h"
#include "Player.h"
class Scene;
class GameEngine
{
private:
	sf::RenderWindow* _window;
	sf::VideoMode _video;
	sf::Event _event;
	std::string header;
	bool fullscreen;
	sf::Clock deltaClock;
	float deltaTime;
	std::map<std::string, int> supportedKeys;  //mapa para guardar valores de keys, sirven como vectores

	std::stack<Scene*> scenes;
	std::stack<LuaReader*> luaScripts;

	void InitKeys();
	void InitWindow();
	void InitScene();


public:
	GameEngine();
	~GameEngine();

	const bool GetWindowOpen();

	void Update();
	void Render();
	void UpdateDeltaTime();
};

