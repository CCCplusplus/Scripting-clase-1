#pragma once
#include "Scene.h"
#include "GameEngine.h"
#include "Button.h"
class Editor : public Scene
{
private:
	sf::RectangleShape _rect;
	sf::Texture BackgroundI;
	sf::Font _font;
	sf::Music song;
	std::map<std::string, GUI::Button*> buttons;

protected:
	void InitKeys();

public:
	Editor(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys,
		std::stack<Scene*>* _scenes, std::stack<LuaReader*>* _luaScripts);

	virtual ~Editor();
	void InitLua();
	void RegisterCPPFunctions(lua_State* L);
	void InitButton();
	void InitBackground();

	static int SetFontFileLua(lua_State* L);
	static int SetBackgroundTextureLua(lua_State* L);
	static int SetMusicFileLua(lua_State* L);
	static int SetMusicVolumeLua(lua_State* L);

	void Update(const float& dt);

	void UpdateButtons(const float& dt);

	void Render(sf::RenderTarget* _target);
};

