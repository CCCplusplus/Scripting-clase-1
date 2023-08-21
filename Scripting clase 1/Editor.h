#pragma once
#include "Scene.h"
#include "GameEngine.h"
class Editor : public Scene
{
private:
	sf::RectangleShape _rect;



protected:
	void InitKeys();

public:
	Editor(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys,
		std::stack<Scene*>* _scenes, std::stack<LuaReader*>* _luaScripts);

	virtual ~Editor();

	void InitLua();

	void RegisterCPPFunctions(lua_State* L);

	void Update(const float& dt);

	void Render(sf::RenderTarget* _target);
};

