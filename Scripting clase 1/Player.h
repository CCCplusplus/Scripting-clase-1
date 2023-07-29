#pragma once
#include "Entity.h"
class Player : public Entity
{
private:

protected:
	

public:
	Player(const float X, const float Y);
	virtual ~Player();

	virtual void Update(const float& dt);	
};

