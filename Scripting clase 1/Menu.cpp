#include "pch.h"
#include "Menu.h"
#include "GameScene.h"
#include "Editor.h"

void Menu::InitBackground()
{
	_rect.setSize(sf::Vector2f(_window->getSize()));
	_rect.setFillColor(sf::Color::White);
}

void Menu::InitFont()
{
	_font.loadFromFile("OptimusPrinceps.ttf");
}

void Menu::InitButton()
{
	buttons ["New Game"] = new GUI::Button(100, 100, 350, 250, &_font,
		"New Button", 50, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color::Red, sf::Color::Cyan, sf::Color::Black, -1);
	buttons ["Settings"] = new GUI::Button(500, 100, 350, 250, &_font,
		"Newer Button", 50, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color::Red, sf::Color::Cyan, sf::Color::Black, 1);

	buttons ["Quit"] = new GUI::Button(900, 100, 350, 250, &_font,
		"Newest Button", 50, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color::Red, sf::Color::Cyan, sf::Color::Black, 2);

}

void Menu::InitBGTexture()
{
	BackgroundI.loadFromFile("MainMenuBG.jpg");
	_rect.setTexture(&BackgroundI);
}

void Menu::InitLua()
{
	_luaReader = new LuaReader("MainMenuSceneLua.lua");
	lua_pushlightuserdata(this->_luaReader->getLuaState(), this);
	lua_setglobal(this->_luaReader->getLuaState(), "MENU");
	this->RegisterCPPFunctions(_luaReader->getLuaState());
	this->_luaReader->LoadFile();
}

void Menu::RegisterCPPFunctions(lua_State* L)
{
}

void Menu::InitKeys()
{
	menuKeys["ONETOTHELEFT"] = supportedKeys->at("A");
	menuKeys["ONETOTHERIGHT"] = supportedKeys->at("D");
	menuKeys["ONEUP"] = supportedKeys->at("W");
	menuKeys["ONEDOWN"] = supportedKeys->at("S");
	menuKeys["DIE"] = supportedKeys->at("Escape");
	menuKeys["CHANGEE"] = supportedKeys->at("C");
	menuKeys["PAUSITA"] = supportedKeys->at("E");
}



Menu::Menu(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys, std::stack<Scene*>* _scenes, std::stack<LuaReader*>* _luaScripts)
	: Scene(_target, _supportKeys, _scenes, _luaScripts)
{
	InitKeys();
	InitFont();
	InitButton();
	InitBackground();
	InitBGTexture();
	InitLua();
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
		scene->push(new GameScene(_window, supportedKeys, scene, luaScripts));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(menuKeys.at("PAUSITA"))))
	{
		std::cout << "You do nothing! You lose!" << "\n";
	}
	UpdateMousePos();
	UpdateButtons(dt);
	ExecuteLuaUpdate();
}

void Menu::UpdateButtons(const float& dt)
{
	for (auto b : buttons)
	{
		b.second->Update(mousePosView);
	}
	if (buttons["New Game"]->GetButtonPress()) 
	{
		scene->push(new GameScene(_window, supportedKeys, scene, luaScripts));
	}
	if (buttons["Settings"]->GetButtonPress())
	{
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
