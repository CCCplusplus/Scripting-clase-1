#include "pch.h"
#include "Entity.h"

Entity::Entity()
{
	hp = 100;

	isActive = true;
}

Entity::~Entity()
{
}

void Entity::InitSpirte(sf::Texture& _texture)
{
	_sprite.setTexture(_texture);
	_hitboxInstance.Init(_texture, _sprite.getPosition());
}


void Entity::Dispara()
{
}

void Entity::Die()
{
	isActive = false;
}

bool Entity::Alive()
{
	if (isActive) return true;
	else {} return false;
}


void Entity::TakeDamage(int damageAmount)
{
	hp -= damageAmount;
}


void Entity::SetPosition(const float x, const float y)
{
	_sprite.setPosition(sf::Vector2f(x, y));
}

void Entity::Move(const float x, const float y, const float& dt, sf::Vector2u windowSize)
{
	float xvalue = 0;
	xvalue += x * moveSpeed * dt;
	float yvalue = 0;
	yvalue += y * moveSpeed * dt;

	_sprite.move(sf::Vector2f(xvalue, yvalue));

	_hitboxInstance.Follow(_sprite, x, y, dt, windowSize);

	//Cuando un entity llegue a el limite de la pantalla se pasara al otro lado.
	if (_sprite.getPosition().x > windowSize.x)
	{
		_sprite.setPosition(0, _sprite.getPosition().y);
		
	}
	else if (_sprite.getPosition().x + _sprite.getTexture()->getSize().x < 0)
	{
		_sprite.setPosition(windowSize.x, _sprite.getPosition().y);
		
	}
	if (_sprite.getPosition().y > windowSize.y)
	{
		_sprite.setPosition(_sprite.getPosition().x, 0);
		
	}
	else if (_sprite.getPosition().y + _sprite.getTexture()->getSize().y < 0)
	{
		_sprite.setPosition(_sprite.getPosition().x, windowSize.y);
		
	}
}

sf::Vector2f Entity::GetPosition() const
{
	return _sprite.getPosition();
}

void Entity::Update(const float& dt, sf::Vector2u windowSize)
{
	if (isActive)
	{

		if (hp <= 0)
		{
			Die();
		}
	}
}

void Entity::Render(sf::RenderTarget* _target)
{
	if (isActive) 
	{
		_target->draw(_sprite);

		_hitboxInstance.Render(_target);
	}
}

