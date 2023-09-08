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
	editorKeys["CHANGEG"] = supportedKeys->at("Space");
	editorKeys["Pausation"] = supportedKeys->at("E");
}


Editor::Editor(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys, std::stack<Scene*>* _scenes, std::stack<LuaReader*>* _luaScripts)
	: Scene(_target, _supportKeys, _scenes, _luaScripts)
{
	InitKeys();
	InitButton();
	InitBackground();
	InitLua();
	song.play();
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

	lua_getglobal(_luaReader->getLuaState(), "InitializeEditor");
	if (lua_pcall(_luaReader->getLuaState(), 0, 0, 0) != 0)
		std::cerr << "Error al llamar a InitializeEditor: " << lua_tostring(_luaReader->getLuaState(), -1) << std::endl;
}

void Editor::RegisterCPPFunctions(lua_State* L)
{
	lua_register(L, "setFontFile", SetFontFileLua);
	lua_register(L, "setBackgroundTexture", SetBackgroundTextureLua);
	lua_register(L, "setMusicFile", SetMusicFileLua);
	lua_register(L, "setMusicVolume", SetMusicVolumeLua);
}

void Editor::InitButton()
{
	buttons["Restart"] = new GUI::Button(700, 100, 350, 250, &_font,
		"Restart", 50, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color::Red, sf::Color::Cyan, sf::Color::Black, -1);
	buttons["QUIT"] = new GUI::Button(700, 500, 350, 250, &_font,
		"Quit", 50, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color::Red, sf::Color::Cyan, sf::Color::Black, 1);
}

void Editor::InitBackground()
{
	_rect.setSize(sf::Vector2f(_window->getSize()));
	_rect.setFillColor(sf::Color::White);
}

int Editor::SetFontFileLua(lua_State* L) {
	lua_getglobal(L, "EDITOR");
	Editor* editor = (Editor*)lua_touserdata(L, -1);
	const char* fontname = lua_tostring(L, 1);
	editor->_font.loadFromFile(fontname);
	return 0;
}

int Editor::SetBackgroundTextureLua(lua_State* L) {
	lua_getglobal(L, "EDITOR");
	Editor* editor = (Editor*)lua_touserdata(L, -1);
	const char* texturename = lua_tostring(L, 1);
	editor->BackgroundI.loadFromFile(texturename);
	editor->_rect.setTexture(&editor->BackgroundI);
	return 0;
}

int Editor::SetMusicFileLua(lua_State* L) {
	lua_getglobal(L, "EDITOR");
	Editor* editor = (Editor*)lua_touserdata(L, -1);
	const char* filename = lua_tostring(L, 1);
	editor->song.openFromFile(filename);
	return 0;
}

int Editor::SetMusicVolumeLua(lua_State* L) {
	lua_getglobal(L, "EDITOR");
	Editor* editor = (Editor*)lua_touserdata(L, -1);
	float volume = lua_tonumber(L, 1);
	editor->song.setVolume(volume);
	return 0;
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
	
	UpdateMousePos();
	UpdateButtons(dt);
}

void Editor::UpdateButtons(const float& dt)
{
	for (auto b : buttons)
	{
		b.second->Update(mousePosView);
	}
	if (buttons["Restart"]->GetButtonPress())
	{
		song.stop();
		scene->push(new GameScene(_window, supportedKeys, scene, luaScripts));
	}
	if (buttons["QUIT"]->GetButtonPress())
	{
		EndState();
	}
}



void Editor::Render(sf::RenderTarget* _target)
{
	_target->draw(_rect);

	_target->draw(_rect);
	for (auto b : buttons)
	{
		b.second->Render(_target);
	}
}
