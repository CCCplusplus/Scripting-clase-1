#pragma once
#include "Scene.h"
#include "Player.h"
#include "GameEngine.h"
#include "Player.h"
#include "Enemy.h"

class Bullets;
class Enemy;
class Player;

class GameScene : public Scene
{
private:
	sf::RectangleShape _rect;
	sf::Texture BackgroundI;
	sf::Texture PlayerI;
	sf::Texture EnemyI;

	Player* _player;

	Enemy* _Baddie;

	std::vector<Bullets*> activeBullets;
	std::vector<Bullets*> playerBullets;

protected:

	void InitKeys();
	void InitPlayer();
	void InitEnemy();
	void InitBG();
	void InitBGTexture();

	void InitLua();

	void RegisterCPPFunctions(lua_State* L);

public:
	GameScene(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys,
		std::stack<Scene*>* _scenes, std::stack<LuaReader*>* _luaScripts);

	virtual ~GameScene();

	void Update(const float& dt);

	void Render(sf::RenderTarget* _target);

	void AddBullet(Bullets* bullet);
	void AddPBullet(Bullets* bullet);
};

