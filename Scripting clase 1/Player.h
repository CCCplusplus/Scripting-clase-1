#pragma once
#include "Entity.h"
#include "Bullets.h"
#include "GameScene.h"

class GameScene;

class Player : public Entity
{
private:
	Bullets* bullets;

protected:
	sf::Texture PlayerT;
	sf::Texture BulletT;

	bool facingRight;

public:
	Player(sf::Texture& _texture, const float X, const float Y);

	virtual ~Player();

	void Flip();

	void Dispara();

	bool State();

	int GetHP();

	GameScene* gameboy;
};

