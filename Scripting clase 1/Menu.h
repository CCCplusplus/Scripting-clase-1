#pragma once
#include "Scene.h"
#include "GameEngine.h"
#include "Button.h"

class Menu : public Scene
{
private:
	sf::RectangleShape _rect;
	sf::Font _font;
	sf::Texture BackgroundI;
	sf::Music song;

	std::map<std::string, GUI::Button*> buttons;

	

	void InitBackground();
	void InitButton();


	void InitLua();

	void RegisterCPPFunctions(lua_State* L);

	static int SetMusicFileLua(lua_State* L);
	static int SetMusicVolumeLua(lua_State* L);
	static int SetFontFileLua(lua_State* L);
	static int SetBackgroundTextureLua(lua_State* L);

protected:
	void InitKeys();

public:
	Menu(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys,
		std::stack<Scene*>* _scenes, std::stack<LuaReader*>* _luaScripts);

	virtual ~Menu();

	void Update(const float& dt);

	void UpdateButtons(const float& dt);

	void Render(sf::RenderTarget* _target);
};

