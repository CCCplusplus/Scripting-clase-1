#include "pch.h"
#include "GameScene.h"
#include "Editor.h"

GameScene::GameScene(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys, std::stack<Scene*>* _scenes, std::stack<LuaReader*>* _luaScripts)
	: Scene(_target, _supportKeys, _scenes, _luaScripts)
{
	InitKeys();
	InitPlayer();
	InitEnemy();
	InitBG();
	InitBGTexture();
	isPaused = false;
	InitLua();
}

GameScene::~GameScene()
{
	delete _player;
}

void GameScene::InitKeys() 
{
	newKeys["MOVE_LEFT"] = supportedKeys->at("A");
	newKeys["MOVE_RIGHT"] = supportedKeys->at("D");
	newKeys["MOVE_UP"] = supportedKeys->at("W");
	newKeys["MOVE_DOWN"] = supportedKeys->at("S");
	newKeys["CLOSE"] = supportedKeys->at("Escape");
	newKeys["CHANGEM"] = supportedKeys->at("C");
	newKeys["PAUSE"] = supportedKeys->at("E");
}

void GameScene::InitPlayer()
{
	PlayerI.loadFromFile("Player.png");
	_player = new Player(PlayerI, 10, 10);
}

void GameScene::InitEnemy()
{
	EnemyI.loadFromFile("Enemy.png");
	_Baddie = new Enemy(EnemyI, 400, 400, _player);
}

void GameScene::InitBG()
{
	_rect.setSize(sf::Vector2f(_window->getSize()));
	_rect.setFillColor(sf::Color::Blue);
}

void GameScene::InitBGTexture()
{
	BackgroundI.loadFromFile("GameSceneBG.jpg");
	_rect.setTexture(&BackgroundI);
}

void GameScene::InitLua()
{
	_luaReader = new LuaReader("GameSceneLua.lua");
	lua_pushlightuserdata(this->_luaReader->getLuaState(), this);
	lua_setglobal(this->_luaReader->getLuaState(), "GAME");
	this->RegisterCPPFunctions(_luaReader->getLuaState());
	this->_luaReader->LoadFile();
}

void GameScene::RegisterCPPFunctions(lua_State* L)
{

}

void GameScene::Update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("PAUSE"))))
	{
		isPaused = !isPaused;
	}
	if (!isPaused) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("MOVE_LEFT"))))
		{
			_player->Move(-1, 0, dt, _window->getSize());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("MOVE_RIGHT"))))
		{
			_player->Move(1, 0, dt, _window->getSize());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("MOVE_UP"))))
		{
			_player->Move(0, -1, dt, _window->getSize());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("MOVE_DOWN"))))
		{
			_player->Move(0, 1, dt, _window->getSize());
		}

		ExecuteLuaUpdate();
		_Baddie->Update(dt, _window->getSize());
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("CLOSE"))))
	{
		EndState();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("CHANGEM"))))
	{
		scene->push(new Editor(_window, supportedKeys, scene, luaScripts));
	}
}

void GameScene::Render(sf::RenderTarget* _target)
{
	_target->draw(_rect);

	_player->Render(_target);

	_Baddie->Render(_target);
}
