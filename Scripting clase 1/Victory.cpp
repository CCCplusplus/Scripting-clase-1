#include "pch.h"
#include "Victory.h"
#include "GameScene.h"

void Victory::InitKeys()
{
	menuKeys["OUTA"] = supportedKeys->at("A");
	menuKeys["OUTD"] = supportedKeys->at("D");
	menuKeys["OUTW"] = supportedKeys->at("W");
	menuKeys["OUTS"] = supportedKeys->at("S");
	menuKeys["OUTESCAPE"] = supportedKeys->at("Escape");
	menuKeys["RESTART"] = supportedKeys->at("Space");
	menuKeys["OUTE"] = supportedKeys->at("E");
}

Victory::Victory(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys, std::stack<Scene*>* _scenes, std::stack<LuaReader*>* _luaScripts)
	: Scene(_target, _supportKeys, _scenes, _luaScripts)
{
	InitKeys();
	InitBackground();
	InitLua();
	song.play();
}

Victory::~Victory()
{
}

void Victory::InitLua()
{
	_luaReader = new LuaReader("VictoryScene.lua");
	lua_pushlightuserdata(this->_luaReader->getLuaState(), this);
	lua_setglobal(this->_luaReader->getLuaState(), "VICTORY");
	this->RegisterCPPFunctions(_luaReader->getLuaState());
	this->_luaReader->LoadFile();

	lua_getglobal(_luaReader->getLuaState(), "InitializeVictory");
	if (lua_pcall(_luaReader->getLuaState(), 0, 0, 0) != 0)
		std::cerr << "Error al llamar a InitializeMainMenu: " << lua_tostring(_luaReader->getLuaState(), -1) << std::endl;
}

void Victory::RegisterCPPFunctions(lua_State* L)
{
	lua_register(L, "setVictoryMusicFile", SetVictoryMusicFileLua);
    lua_register(L, "setVictoryMusicVolume", SetVictoryMusicVolumeLua);
    lua_register(L, "setVictoryBackgroundTexture", SetVictoryBackgroundTextureLua);
}

int Victory::SetVictoryMusicFileLua(lua_State* L) {
	lua_getglobal(L, "VICTORY");
	Victory* victory = (Victory*)lua_touserdata(L, -1);
	const char* filename = lua_tostring(L, 1);
	victory->song.openFromFile(filename);
	return 0;
}

int Victory::SetVictoryMusicVolumeLua(lua_State* L) {
	lua_getglobal(L, "VICTORY");
	Victory* victory = (Victory*)lua_touserdata(L, -1);
	float volume = lua_tonumber(L, 1);
	victory->song.setVolume(volume);
	return 0;
}

int Victory::SetVictoryBackgroundTextureLua(lua_State* L) {
	lua_getglobal(L, "VICTORY");
	Victory* victory = (Victory*)lua_touserdata(L, -1);
	const char* texturename = lua_tostring(L, 1);
	victory->BackgroundI.loadFromFile(texturename);
	victory->_rect.setTexture(&victory->BackgroundI);
	return 0;
}


void Victory::InitBackground()
{
	_rect.setSize(sf::Vector2f(_window->getSize()));
	_rect.setFillColor(sf::Color::White);
}


void Victory::Update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("OUTA"))))
	{
		EndState();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("OUTD"))))
	{
		EndState();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("OUTW"))))
	{
		EndState();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("OUTS"))))
	{
		EndState();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("OUTESCAPE"))))
	{
		EndState();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("RESTART"))))
	{
		scene->push(new GameScene(_window, supportedKeys, scene, luaScripts));
		song.stop();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("OUTE"))))
	{
		EndState();
	}
}

void Victory::Render(sf::RenderTarget* _target)
{
	_target->draw(_rect);
}
