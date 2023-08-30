#pragma once
#include "Scene.h"

class Victory : public Scene
{
private:
	sf::RectangleShape _rect;
	sf::Texture BackgroundI;

	void InitLua();

	void RegisterCPPFunctions(lua_State* L);

	void InitBackground();

	void InitBGTexture();

protected:
	void InitKeys();

public:

	Victory(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys,
		std::stack<Scene*>* _scenes, std::stack<LuaReader*>* _luaScripts);

	~Victory();

	void Update(const float& dt);

	void Render(sf::RenderTarget* _target);
};

