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
	sf::Texture PBulletT;
	sf::Texture EBulletT;

	Player* _player;

	Enemy* _Baddie;

	std::vector<Bullets*> activeBullets;
	std::deque<Bullets*> inactivePlayerBullets;
	std::deque<Bullets*> inactiveEnemyBullets;
	std::vector<Bullets*> playerBullets;
	sf::Font _font;
	sf::Text hpText;
	float downtime;

protected:

	void InitKeys();
	void InitPlayer();
	void InitEnemy();
	void InitBG();
	void InitBGTexture();
	void InitFont();
	void InitText();
	void InitBullets();
	void InitBulletT();
	void InitLua();

	void RegisterCPPFunctions(lua_State* L);

public:
	GameScene(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys,
		std::stack<Scene*>* _scenes, std::stack<LuaReader*>* _luaScripts);

	virtual ~GameScene();

	void Update(const float& dt);

	void Render(sf::RenderTarget* _target);

	void AddBullet();
	void AddPBullet();

	void ReusePlayerBullets();
	void ReuseEnemyBullets();

};

