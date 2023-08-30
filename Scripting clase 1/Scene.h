#pragma once
#include "LuaReader.h"
class Scene
{
private:
	 

protected:
	sf::RenderWindow* _window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> newKeys;
	std::map<std::string, int> menuKeys;
	std::map<std::string, int> editorKeys;
	std::map<std::string, int> victorykeys;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosWindow;
	sf::Vector2i mousePosScreen;
	sf::Vector2u mousePosGrid;


	virtual void InitKeys() = 0;

	LuaReader *_luaReader;

public:
	Scene(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys,
		std::stack<Scene*>* _scenes, std::stack<LuaReader*>* _luaScripts);

	virtual ~Scene();

	virtual void EndState();

	virtual void Update(const float& dt) = 0;

	virtual void Render(sf::RenderTarget* _target) = 0;

	virtual void  InitLua();
	
	virtual void ExecuteLuaUpdate();
	virtual void ExecuteLuaRender();

	virtual void UpdateMousePos();

	const bool GetQuit();

	std::stack<Scene*>* scene;
	std::stack<LuaReader*>* luaScripts;

	bool quit;

	bool isPaused;

	//update es para tiempo, Render para dibujo
	//Llamar a las dos funciones en el render y el update de GameEngine
};

