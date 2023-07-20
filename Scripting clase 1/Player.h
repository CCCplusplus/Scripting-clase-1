#pragma once
#include "Entity.h"
class Player : public Entity
{
private:
	sf::RectangleShape _rect;

public:
	void Update(sf::RenderWindow*) override;

	void Render(sf::RenderWindow*) override;
};

