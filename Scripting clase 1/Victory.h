#pragma once
#include "Scene.h"

class Victory : public Scene
{
private:
	sf::RectangleShape _rect;
	sf::Texture BackgroundI;
	sf::Music song;

	void InitLua();

	void RegisterCPPFunctions(lua_State* L);

	void InitBackground();

	static int SetVictoryMusicFileLua(lua_State* L);
	static int SetVictoryMusicVolumeLua(lua_State* L);
	static int SetVictoryBackgroundTextureLua(lua_State* L);

protected:
	void InitKeys();

public:

	Victory(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys,
		std::stack<Scene*>* _scenes, std::stack<LuaReader*>* _luaScripts);

	~Victory();

	void Update(const float& dt);

	void Render(sf::RenderTarget* _target);
};

