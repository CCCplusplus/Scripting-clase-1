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
	InitBGTexture();
	InitLua();
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
}

void Victory::RegisterCPPFunctions(lua_State* L)
{
}

void Victory::InitBackground()
{
	_rect.setSize(sf::Vector2f(_window->getSize()));
	_rect.setFillColor(sf::Color::White);
}

void Victory::InitBGTexture()
{
	BackgroundI.loadFromFile("Win.jpg");
	_rect.setTexture(&BackgroundI);
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
