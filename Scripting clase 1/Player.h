#pragma once
#include "Entity.h"
class Player : public Entity
{
private:

protected:
	sf::Texture PlayerT;

public:
	Player(sf::Texture& _texture, const float X, const float Y);

	virtual ~Player();

	virtual void Update(const float& dt);	
};

