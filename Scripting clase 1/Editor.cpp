#include "pch.h"
#include "Editor.h"
#include "Menu.h"

void Editor::InitKeys()
{
	editorKeys["E-LEFT"] = supportedKeys->at("A");
	editorKeys["E-RIGHT"] = supportedKeys->at("D");
	editorKeys["E-UP"] = supportedKeys->at("W");
	editorKeys["E-DOWN"] = supportedKeys->at("S");
	editorKeys["MURDERIZE"] = supportedKeys->at("Escape");
	editorKeys["CHANGEG"] = supportedKeys->at("C");
	editorKeys["Pausation"] = supportedKeys->at("E");
}

Editor::Editor(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys, std::stack<Scene*>* _scenes, std::stack<LuaReader*>* _luaScripts)
	: Scene(_target, _supportKeys, _scenes, _luaScripts)
{
	InitKeys();
	_rect.setSize(sf::Vector2f(_window->getSize()));
	_rect.setFillColor(sf::Color::Magenta);
}

Editor::~Editor()
{
}

void Editor::InitLua()
{
	_luaReader = new LuaReader("EditorSceneLua.lua");
	lua_pushlightuserdata(this->_luaReader->getLuaState(), this);
	lua_setglobal(this->_luaReader->getLuaState(), "EDITOR");
	this->RegisterCPPFunctions(_luaReader->getLuaState());
	this->_luaReader->LoadFile();
}

void Editor::RegisterCPPFunctions(lua_State* L)
{

}

void Editor::Update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorKeys.at("E-LEFT"))))
	{
		std::cout << "Izquierda-Editada" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorKeys.at("E-RIGHT"))))
	{
		std::cout << "Derecha-Editada" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorKeys.at("E-UP"))))
	{
		std::cout << "Arriba-Editada" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorKeys.at("E-DOWN"))))
	{
		std::cout << "Abajo-Editado" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorKeys.at("MURDERIZE"))))
	{
		EndState();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorKeys.at("CHANGEG"))))
	{
		scene->push(new Menu(_window, supportedKeys, scene, luaScripts));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorKeys.at("Pausation"))))
	{
		std::cout << "You do nothing! You lose!" << "\n";
	}

	//ExecuteLuaUpdate();
}

void Editor::Render(sf::RenderTarget* _target)
{
	_target->draw(_rect);
}
