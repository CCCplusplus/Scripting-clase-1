#pragma once
#include "Hitbox.h"
class Entity
{
private:

protected:
	float moveSpeed;
	int hp;
	sf::Sprite _sprite;
	Hitbox _hitboxInstance;

public:
	Entity();

	~Entity();

	void InitSpirte(sf::Texture& _texture);

	void InitMovement();


	virtual void SetPosition(const float x, const float y);

	virtual void Move(const float x, const float y, const float& dt, sf::Vector2u windowSize);

	sf::Vector2f GetPosition() const;

	virtual void Update(const float& dt, sf::Vector2u windowSize);

	void Render(sf::RenderTarget* _target);
};

