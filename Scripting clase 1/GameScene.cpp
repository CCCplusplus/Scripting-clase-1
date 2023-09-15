#include "pch.h"
#include "GameScene.h"
#include "Editor.h"
#include "Victory.h"

GameScene::GameScene(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys, std::stack<Scene*>* _scenes, std::stack<LuaReader*>* _luaScripts)
	: Scene(_target, _supportKeys, _scenes, _luaScripts)
{
	InitLua();
	InitPlayer();
	InitKeys();
	InitBG();
	InitBullets();
	isPaused = false;
	song.play();
	enemySpawnTimer = enemySpawnInterval;
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
	newKeys["CHANGEM"] = supportedKeys->at("Space");
	newKeys["PAUSE"] = supportedKeys->at("E");
}

void GameScene::InitPlayer()
{
	PlayerI.loadFromFile("Player.png");
	_player = new Player(PlayerI, 200, 200);
	_player->gameboy = this;
}



void GameScene::InitLua()
{
	_luaReader = new LuaReader("GameSceneLua.lua");
	lua_pushlightuserdata(this->_luaReader->getLuaState(), this);
	lua_setglobal(this->_luaReader->getLuaState(), "GAME");
	this->RegisterCPPFunctions(_luaReader->getLuaState());
	this->_luaReader->LoadFile();

	lua_getglobal(_luaReader->getLuaState(), "InitializeGameValues");
	if (lua_pcall(_luaReader->getLuaState(), 0, 0, 0) != 0)
		std::cerr << "Error al llamar a InitializeGameValues: " << lua_tostring(_luaReader->getLuaState(), -1) << std::endl;

	lua_getglobal(_luaReader->getLuaState(), "InitializeGameScene");
	if (lua_pcall(_luaReader->getLuaState(), 0, 0, 0) != 0)
		std::cerr << "Error al llamar a InitializeGameScene: " << lua_tostring(_luaReader->getLuaState(), -1) << std::endl;
}

void GameScene::RegisterCPPFunctions(lua_State* L)
{
	lua_register(L, "setEnemySprite", SetEnemySpriteLua);
	lua_register(L, "setBackgroundTexture", SetBackgroundTextureLua);
	lua_register(L, "setGameFont", SetFontFileLua);
	lua_register(L, "setHPTextAttributes", SetHPTextAttributesLua);
	lua_register(L, "setVictoryCounterAttributes", SetVictoryCounterAttributesLua);
	lua_register(L, "setBulletTextures", SetBulletTexturesLua);
	lua_register(L, "setMusicFile", SetMusicFileLua);
	lua_register(L, "setMusicVolume", SetMusicVolumeLua);
	lua_register(L, "setVictoryValue", SetVictoryLua);
	lua_register(L, "setDowntimeValue", SetDowntimeLua);
	lua_register(L, "setPausetimeValue", SetPausetimeLua);
	lua_register(L, "setQuittimeValue", SetQuittimeLua);
	lua_register(L, "setActiveEnemiesValue", SetActiveEnemiesLua);
}

int GameScene::SetEnemySpriteLua(lua_State* L) {
	lua_getglobal(L, "GAME");
	GameScene* game = (GameScene*)lua_touserdata(L, -1);
	const char* filename = lua_tostring(L, 1);
	game->EnemyI.loadFromFile(filename);
	return 0;
}

int GameScene::SetBackgroundTextureLua(lua_State* L) {
	lua_getglobal(L, "GAME");
	GameScene* game = (GameScene*)lua_touserdata(L, -1);
	const char* texturename = lua_tostring(L, 1);
	game->BackgroundI.loadFromFile(texturename);
	game->_rect.setTexture(&game->BackgroundI);
	return 0;
}

int GameScene::SetFontFileLua(lua_State* L) {
	lua_getglobal(L, "GAME");
	GameScene* game = (GameScene*)lua_touserdata(L, -1);
	const char* fontname = lua_tostring(L, 1);
	game->_font.loadFromFile(fontname);
	return 0;
}

int GameScene::SetHPTextAttributesLua(lua_State* L) {
	lua_getglobal(L, "GAME");
	GameScene* game = (GameScene*)lua_touserdata(L, -1);
	int fontSize = lua_tonumber(L, 1);
	const char* colorStr = lua_tostring(L, 2);
	float x = lua_tonumber(L, 3);
	float y = lua_tonumber(L, 4);
	game->hpText.setFont(game->_font);
	game->hpText.setCharacterSize(fontSize);
	game->hpText.setPosition(x, y);
	game->hpText.setFillColor(sf::Color::White);
	return 0;
}

int GameScene::SetVictoryCounterAttributesLua(lua_State* L) {
	lua_getglobal(L, "GAME");
	GameScene* game = (GameScene*)lua_touserdata(L, -1);
	int fontSize = lua_tonumber(L, 1);
	const char* colorStr = lua_tostring(L, 2);
	float x = lua_tonumber(L, 3);
	float y = lua_tonumber(L, 4);
	game->victoryCounter.setFont(game->_font);
	game->victoryCounter.setCharacterSize(fontSize);
	game->victoryCounter.setPosition(x, y);
	game->hpText.setFillColor(sf::Color::White);
	return 0;
}


int GameScene::SetBulletTexturesLua(lua_State* L) {
	lua_getglobal(L, "GAME");
	GameScene* game = (GameScene*)lua_touserdata(L, -1);
	const char* bulletPFile = lua_tostring(L, 1);
	const char* bulletEFile = lua_tostring(L, 2);
	game->PBulletT.loadFromFile(bulletPFile);
	game->EBulletT.loadFromFile(bulletEFile);
	return 0;
}

int GameScene::SetMusicFileLua(lua_State* L) {
	lua_getglobal(L, "GAME");
	GameScene* game = (GameScene*)lua_touserdata(L, -1);
	const char* musicfile = lua_tostring(L, 1);
	game->song.openFromFile(musicfile);
	return 0;
}

int GameScene::SetMusicVolumeLua(lua_State* L) {
	lua_getglobal(L, "GAME");
	GameScene* game = (GameScene*)lua_touserdata(L, -1);
	float volume = lua_tonumber(L, 1);
	game->song.setVolume(volume);
	return 0;
}

int GameScene::SetVictoryLua(lua_State* L) {
	lua_getglobal(L, "GAME");
	GameScene* game = (GameScene*)lua_touserdata(L, -1);
	int value = lua_tointeger(L, 1);
	game->victory = value;
	return 0;
}

int GameScene::SetDowntimeLua(lua_State* L) {
	lua_getglobal(L, "GAME");
	GameScene* game = (GameScene*)lua_touserdata(L, -1);
	float value = lua_tonumber(L, 1);
	game->downtime = value;
	return 0;
}

int GameScene::SetPausetimeLua(lua_State* L) {
	lua_getglobal(L, "GAME");
	GameScene* game = (GameScene*)lua_touserdata(L, -1);
	float value = lua_tonumber(L, 1);
	game->pausetime = value;
	return 0;
}

int GameScene::SetQuittimeLua(lua_State* L) {
	lua_getglobal(L, "GAME");
	GameScene* game = (GameScene*)lua_touserdata(L, -1);
	float value = lua_tonumber(L, 1);
	game->quittime = value;
	return 0;
}

int GameScene::SetActiveEnemiesLua(lua_State* L) {
	lua_getglobal(L, "GAME");
	GameScene* game = (GameScene*)lua_touserdata(L, -1);
	int value = lua_tointeger(L, 1);
	game->activeenemies = value;
	return 0;
}

void GameScene::SpawnEnemy()
{
	if (activeenemies < maxEnemies) {
		Enemy* enemy = new Enemy(EnemyI, 400, 900, _player);
		enemy->gameSceneInstance = this;
		_Baddies.push_back(enemy);
		activeenemies++;
	}
}

void GameScene::InitBG()
{
	_rect.setSize(sf::Vector2f(_window->getSize()));
	_rect.setFillColor(sf::Color::Blue);
}


void GameScene::InitBullets()
{
	for (int i = 0; i < 30; ++i) {
		Bullets* bullet = new Bullets(PBulletT, _player->GetPosition().x + 20, _player->GetPosition().y, 40);
		bullet->Deactivate();
		inactivePlayerBullets.push_back(bullet);
	}

	for (int i = 0; i < 90; ++i) {
		Bullets* bullet = new Bullets(EBulletT, 400, 900, 50);
		bullet->Deactivate();
		inactiveEnemyBullets.push_back(bullet);
	}
}

void GameScene::AddBullet() {
	for (Enemy* enemy : _Baddies) {
		if (enemy->Alive() && !inactiveEnemyBullets.empty()) {
			Bullets* bullet = inactiveEnemyBullets.front();
			inactiveEnemyBullets.pop_front();

			bullet->SetPosition(enemy->GetPosition().x + 20, enemy->GetPosition().y);
			bullet->activate(enemy);
			sf::Vector2f direction = _player->GetPosition() - enemy->GetPosition();
			float length = sqrt(direction.x * direction.x + direction.y * direction.y);
			direction.x /= length;
			direction.y /= length;

			float bulletSpeed = 10.0f;
			bullet->SetMoveSpeedX(direction.x * bulletSpeed);
			bullet->SetMoveSpeedY(direction.y * bulletSpeed);

			activeBullets.push_back(bullet);
		}
	}
}



void GameScene::AddPBullet() {
	if (!inactivePlayerBullets.empty()) {
		Bullets* bullet = inactivePlayerBullets.front();
		inactivePlayerBullets.pop_front();

		bullet->SetPosition(_player->GetPosition().x + 20, _player->GetPosition().y);

		bullet->activate(_player);

		if (_player->State()) {
			bullet->SetMoveSpeedX(abs(bullet->GetMoveSpeedX()));
		}
		else {
			bullet->SetMoveSpeedX(-abs(bullet->GetMoveSpeedX()));
		}

		playerBullets.push_back(bullet);
	}
}

void GameScene::ReusePlayerBullets()
{
	for (auto it = playerBullets.begin(); it != playerBullets.end(); ) {
		if (!(*it)->Alive()) {
			(*it)->Deactivate();
			inactivePlayerBullets.push_back(*it);
			it = playerBullets.erase(it);
		}
		else {
			++it;
		}
	}
}

void GameScene::ReuseEnemyBullets()
{
	for (auto it = activeBullets.begin(); it != activeBullets.end(); ) {
		if (!(*it)->Alive()) {
			(*it)->Deactivate();
			inactiveEnemyBullets.push_back(*it);
			it = activeBullets.erase(it);
		}
		else {
			++it;
		}
	}
}


void GameScene::Update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("PAUSE"))))
	{
		if (pausetime  <= 0) {
			pausetime = 0.3f;
			isPaused = !isPaused;
		}
	}
	if (!isPaused) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("MOVE_LEFT"))))
		{
			if (_player->State())
				_player->Flip();
			_player->Move(-1, 0, dt, _window->getSize());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("MOVE_RIGHT"))))
		{
			if (!_player->State())
				_player->Flip();
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("CHANGEM"))))
		{
			if (downtime <= 0) {
				downtime = 1.0f;
				_player->Dispara();
			}
		}

		ReuseEnemyBullets();
		ReusePlayerBullets();

		for (Bullets* bullet : activeBullets)
		{
			bullet->Update(dt, _window->getSize());

			bullet->HandleCollision(_player);
		}

		for (Bullets* bullet : playerBullets) {
			bullet->Update(dt, _window->getSize());
			for (Enemy* enemy : _Baddies) {
				if (enemy->Alive()) {
					bullet->HandleCollision(enemy);
				}
			}
		}


		ExecuteLuaUpdate();
		enemySpawnTimer -= dt;
		if (enemySpawnTimer <= 0) {
			SpawnEnemy();
			enemySpawnTimer = enemySpawnInterval;
		}

		for (Enemy* enemy : _Baddies) {
			if (enemy->Alive()) {
				enemy->Update(dt, _window->getSize());
			}
		}
		if (_player->Alive())
			_player->Update(dt, _window->getSize());
		downtime -= dt;
		
	}
	pausetime -= dt;
	if (!_player->Alive()) {
		song.stop();
		scene->push(new Editor(_window, supportedKeys, scene, luaScripts));
	}
	for (Enemy* enemy : _Baddies) {
		if (enemy->WasAlive() && !enemy->Alive()) {
			activeenemies--;
			victory--;
		}
		enemy->UpdateAliveStatus();
	}

	if (victory <= 0) {
		song.stop();
		scene->push(new Victory(_window, supportedKeys, scene, luaScripts));
	}

	

	std::stringstream ss;
	ss << "HP: " << _player->GetHP();  
	hpText.setString(ss.str());

	std::stringstream sa;
	sa << "Enemy Kills to Win: " << victory;
	victoryCounter.setString(sa.str());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("CLOSE"))))
	{
		if (quittime <= 0) {
			quittime = 0.3f;
			EndState();
		}
	}
	quittime -= dt;
}

void GameScene::Render(sf::RenderTarget* _target)
{
	_target->draw(_rect);

	_player->Render(_target);

	for (Enemy* enemy : _Baddies) {
		if (enemy->Alive()) {
			enemy->Render(_target);
		}
	}

	_target->draw(hpText);

	_target->draw(victoryCounter);

	for (Bullets* bullet : activeBullets)
	{
		bullet->Render(_target);
	}

	for (Bullets* bullet : playerBullets)
	{
		bullet->Render(_target);
	}
}
