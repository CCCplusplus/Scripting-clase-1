#pragma once
#include "Entity.h"
#include "Player.h"
class Enemy : public Entity
{
private:
	Player* _player;

protected:

public:
	Enemy(const float x, const float y, Player* player);

	virtual ~Enemy();

	void SetObjective();

	void MovetoObjective(const float& dt, sf::Vector2u windowSize);

	virtual void Update(const float& dt, sf::Vector2u windowSize);
};

