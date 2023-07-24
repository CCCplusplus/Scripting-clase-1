#pragma once
#include "Entity.h"
class Player : public Entity
{
private:
	

public:
	Player(const float X, const float Y);
	virtual ~Player();

	virtual void Update(const float& dt);	
};

