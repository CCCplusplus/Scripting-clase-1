#pragma once
#include "Scene.h"
#include "Player.h"
#include "GameEngine.h"
#include "Player.h"
#include "Enemy.h"
class GameScene : public Scene
{
private:
	sf::RectangleShape _rect;

	Player* _player;

	Enemy* _Baddie;

protected:

	void InitKeys();
	void InitPlayer();
	void InitEnemy();


public:
	GameScene(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys,
		std::stack<Scene*>* _scenes);

	virtual ~GameScene();

	void Update(const float& dt);

	void Render(sf::RenderTarget* _target);
};

