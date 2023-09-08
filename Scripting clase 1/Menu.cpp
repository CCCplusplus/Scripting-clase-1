#include "pch.h"
#include "Menu.h"
#include "GameScene.h"
#include "Editor.h"
#include "Victory.h"

void Menu::InitBackground()
{
	_rect.setSize(sf::Vector2f(_window->getSize()));
	_rect.setFillColor(sf::Color::White);
}


void Menu::InitButton()
{
	buttons ["New Game"] = new GUI::Button(100, 100, 350, 250, &_font,
		"Start", 50, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color::Red, sf::Color::Cyan, sf::Color::Black, -1);
	buttons ["Settings"] = new GUI::Button(500, 100, 350, 250, &_font,
		"Skip", 50, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color::Red, sf::Color::Cyan, sf::Color::Black, 1);

	buttons ["Quit"] = new GUI::Button(900, 100, 350, 250, &_font,
		"Quit", 50, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color::Red, sf::Color::Cyan, sf::Color::Black, 2);

}

void Menu::InitLua()
{
	_luaReader = new LuaReader("MainMenuSceneLua.lua");
	lua_pushlightuserdata(this->_luaReader->getLuaState(), this);
	lua_setglobal(this->_luaReader->getLuaState(), "MENU");
	this->RegisterCPPFunctions(_luaReader->getLuaState());
	this->_luaReader->LoadFile();

	lua_getglobal(_luaReader->getLuaState(), "InitializeMainMenu");
	if (lua_pcall(_luaReader->getLuaState(), 0, 0, 0) != 0)
		std::cerr << "Error al llamar a InitializeMainMenu: " << lua_tostring(_luaReader->getLuaState(), -1) << std::endl;
	
}

void Menu::RegisterCPPFunctions(lua_State* L)
{
	lua_register(L, "setMusicFile", SetMusicFileLua);
	lua_register(L, "setMusicVolume", SetMusicVolumeLua);
	lua_register(L, "setFontFile", SetFontFileLua);
	lua_register(L, "setBackgroundTexture", SetBackgroundTextureLua);
}

int Menu::SetMusicFileLua(lua_State* L) {
	lua_getglobal(L, "MENU");
	Menu* menu = (Menu*)lua_touserdata(L, -1);
	const char* filename = lua_tostring(L, 1);
	menu->song.openFromFile(filename);
	return 0;
}

int Menu::SetMusicVolumeLua(lua_State* L) {
	lua_getglobal(L, "MENU");
	Menu* menu = (Menu*)lua_touserdata(L, -1);
	float volume = lua_tonumber(L, 1);
	menu->song.setVolume(volume);
	return 0;
}

int Menu::SetFontFileLua(lua_State* L) {
	lua_getglobal(L, "MENU");
	Menu* menu = (Menu*)lua_touserdata(L, -1);
	const char* fontname = lua_tostring(L, 1);
	menu->_font.loadFromFile(fontname);
	return 0;
}

int Menu::SetBackgroundTextureLua(lua_State* L) {
	lua_getglobal(L, "MENU");
	Menu* menu = (Menu*)lua_touserdata(L, -1);
	const char* texturename = lua_tostring(L, 1);
	menu->BackgroundI.loadFromFile(texturename);
	menu->_rect.setTexture(&menu->BackgroundI);
	return 0;
}


void Menu::InitKeys()
{
	menuKeys["ONETOTHELEFT"] = supportedKeys->at("A");
	menuKeys["ONETOTHERIGHT"] = supportedKeys->at("D");
	menuKeys["ONEUP"] = supportedKeys->at("W");
	menuKeys["ONEDOWN"] = supportedKeys->at("S");
	menuKeys["DIE"] = supportedKeys->at("Escape");
	menuKeys["CHANGEE"] = supportedKeys->at("Space");
	menuKeys["PAUSITA"] = supportedKeys->at("E");
}



Menu::Menu(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys, std::stack<Scene*>* _scenes, std::stack<LuaReader*>* _luaScripts)
	: Scene(_target, _supportKeys, _scenes, _luaScripts)
{
	InitKeys();
	InitButton();
	InitBackground();
	InitLua();
	song.play();
}

Menu::~Menu()
{
	for (auto b : buttons)
	{
		delete b.second;
	}
}

void Menu::Update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("ONETOTHELEFT"))))
	{
		std::cout << "movidita a la izquierda" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("ONETOTHERIGHT"))))
	{
		std::cout << "movidita a la derecha" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("ONEUP"))))
	{
		std::cout << "movidita arriba" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("ONEDOWN"))))
	{
		std::cout << "movidita abajo" << "\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("DIE"))))
	{
		EndState();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("CHANGEE"))))
	{
		song.stop();
		scene->push(new GameScene(_window, supportedKeys, scene, luaScripts));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("PAUSITA"))))
	{
		std::cout << "You do nothing! You lose!" << "\n";
		scene->push(new Victory(_window, supportedKeys, scene, luaScripts));
		song.stop();
	}
	UpdateMousePos();
	UpdateButtons(dt);
}

void Menu::UpdateButtons(const float& dt)
{
	for (auto b : buttons)
	{
		b.second->Update(mousePosView);
	}
	if (buttons["New Game"]->GetButtonPress()) 
	{
		song.stop();
		scene->push(new GameScene(_window, supportedKeys, scene, luaScripts));
	}
	if (buttons["Settings"]->GetButtonPress())
	{
		song.stop();
		scene->push(new Editor(_window, supportedKeys, scene, luaScripts));
	}
	if (buttons["Quit"]->GetButtonPress())
	{
		EndState();
	}
	
}



void Menu::Render(sf::RenderTarget* _target)
{
	_target->draw(_rect);
	for (auto b : buttons) 
	{
		b.second->Render(_target);
	}
}
