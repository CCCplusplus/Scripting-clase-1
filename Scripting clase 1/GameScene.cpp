#include "pch.h"
#include "GameScene.h"
#include "Editor.h"
#include "Victory.h"

GameScene::GameScene(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys, std::stack<Scene*>* _scenes, std::stack<LuaReader*>* _luaScripts)
	: Scene(_target, _supportKeys, _scenes, _luaScripts)
{
	InitKeys();
	InitPlayer();
	InitEnemy();
	InitBG();
	InitBGTexture();
	InitBulletT();
	InitBullets();
	InitFont();
	InitText();
	InitMusic();
	isPaused = false;
	InitLua();
	victory = 10;
	downtime = 0.0f;
	song.play();
	activeenemies = 0;
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

void GameScene::InitEnemy()
{
	EnemyI.loadFromFile("Enemy.png");
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

void GameScene::InitBGTexture()
{
	BackgroundI.loadFromFile("GameSceneBG.jpg");
	_rect.setTexture(&BackgroundI);
}

void GameScene::InitFont()
{
	_font.loadFromFile("OptimusPrinceps.ttf");

}

void GameScene::InitText()
{
	hpText.setFont(_font);
	hpText.setCharacterSize(60);
	hpText.setFillColor(sf::Color::White);
	hpText.setPosition(10, 10);

	victoryCounter.setFont(_font);
	victoryCounter.setCharacterSize(60);
	victoryCounter.setFillColor(sf::Color::White);
	victoryCounter.setPosition(1320, 10);
}

void GameScene::InitBullets()
{
	for (int i = 0; i < 30; ++i) {
		Bullets* bullet = new Bullets(PBulletT, _player->GetPosition().x+20, _player->GetPosition().y, 40);
		bullet->Deactivate();
		inactivePlayerBullets.push_back(bullet);
	}

	for (int i = 0; i < 90; ++i) {
		Bullets* bullet = new Bullets(EBulletT, 400, 900, 50);
		bullet->Deactivate();
		inactiveEnemyBullets.push_back(bullet);
	}
}

void GameScene::InitBulletT()
{
	PBulletT.loadFromFile("Hadouken.png");
	EBulletT.loadFromFile("BlackHole.png");
}

void GameScene::InitMusic()
{
	song.openFromFile("Level.mp3");
	song.setVolume(6);
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
		isPaused = !isPaused;
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(newKeys.at("CHANGEM"))))
			{
				if (downtime <= 0) {
					downtime = 2.0f;
					_player->Dispara();
				}
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
		EndState();
	}
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
