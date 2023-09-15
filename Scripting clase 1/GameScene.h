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

	std::vector<Enemy*> _Baddies;
	float enemySpawnTimer;
	const float enemySpawnInterval = 4.0f;
	const int maxEnemies = 3;

	std::vector<Bullets*> activeBullets;
	std::deque<Bullets*> inactivePlayerBullets;
	std::deque<Bullets*> inactiveEnemyBullets;
	std::vector<Bullets*> playerBullets;
	sf::Font _font;
	sf::Text hpText;
	sf::Text victoryCounter;
	sf::Music song;
	float downtime;
	float pausetime;
	int activeenemies;
	int victory;

protected:

	void InitKeys();
	void InitPlayer();
	void SpawnEnemy();
	void InitBG();
	void InitBullets();
	void InitLua();

	void RegisterCPPFunctions(lua_State* L);

	static int SetEnemySpriteLua(lua_State* L);
	static int SetBackgroundTextureLua(lua_State* L);
	static int SetFontFileLua(lua_State* L);
	static int SetHPTextAttributesLua(lua_State* L);
	static int SetVictoryCounterAttributesLua(lua_State* L);
	static int SetBulletTexturesLua(lua_State* L);
	static int SetMusicFileLua(lua_State* L);
	static int SetMusicVolumeLua(lua_State* L);
	static int SetVictoryLua(lua_State* L);
	static int SetDowntimeLua(lua_State* L);
	static int SetPausetimeLua(lua_State* L);
	static int SetQuittimeLua(lua_State* L);
	static int SetActiveEnemiesLua(lua_State* L);


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

