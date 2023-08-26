#pragma once
#include "Hitbox.h"
class Entity
{
private:

protected:
	float moveSpeed;
	float elapsedtime;
	int hp;
	sf::Sprite _sprite;
	bool isActive;

public:
	Entity();

	~Entity();

	void InitSpirte(sf::Texture& _texture);

	void InitMovement();

	virtual void Dispara();

	virtual void Die();

	virtual bool Alive();

	virtual void TakeDamage(int damageAmount);

	virtual void SetPosition(const float x, const float y);

	virtual void Move(const float x, const float y, const float& dt, sf::Vector2u windowSize);

	sf::Vector2f GetPosition() const;

	virtual void Update(const float& dt, sf::Vector2u windowSize);

	void Render(sf::RenderTarget* _target);

	Hitbox _hitboxInstance;
};

