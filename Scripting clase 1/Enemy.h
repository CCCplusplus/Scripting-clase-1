#pragma once
#include "Entity.h"
#include "Player.h"
#include "Bullets.h"
#include "GameScene.h"

class GameScene;
class Player;

class Enemy : public Entity
{
private:
	Player* _player;
	Bullets* bullets;
	int victorycounter;

protected:
	sf::Texture EnemyT;
	sf::Texture EnemyBulletT;

public:
	Enemy(sf::Texture& _texture, const float x, const float y, Player* player);

	virtual ~Enemy();

	void SetObjective();

	void Dispara();

	void Die() override;

	int Victory();

	void MovetoObjective(const float& dt, sf::Vector2u windowSize);

	virtual void Update(const float& dt, sf::Vector2u windowSize);

	GameScene* gameSceneInstance;
};

