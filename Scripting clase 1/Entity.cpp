#include "pch.h"
#include "Entity.h"

Entity::Entity()
{
	moveSpeed = 100;
}

Entity::~Entity()
{
}

void Entity::InitSpirte(sf::Texture& _texture)
{
	_sprite.setTexture(_texture);
}



void Entity::InitHitBox(sf::Texture& imagensize)
{

	_hitbox.setSize(sf::Vector2f(imagensize.getSize().x, imagensize.getSize().y));

	_hitbox.setFillColor(sf::Color::Transparent);

	
	_hitbox.setPosition(_sprite.getPosition());
;

	// Debug ver el contorno del hitbox.
	_hitbox.setOutlineThickness(1.0f);
	_hitbox.setOutlineColor(sf::Color::Red);

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
	_hitbox.move(sf::Vector2f(xvalue, yvalue));

	//Cuando un entity llegue a el limite de la pantalla se pasara al otro lado.
	if (_sprite.getPosition().x > windowSize.x)
	{
		_sprite.setPosition(0, _sprite.getPosition().y);
		_hitbox.setPosition(0, _hitbox.getPosition().y);
	}
	else if (_sprite.getPosition().x + _sprite.getTexture()->getSize().x < 0)
	{
		_sprite.setPosition(windowSize.x, _sprite.getPosition().y);
		_hitbox.setPosition(windowSize.x, _hitbox.getPosition().y);
	}
	if (_sprite.getPosition().y > windowSize.y)
	{
		_sprite.setPosition(_sprite.getPosition().x, 0);
		_hitbox.setPosition(_hitbox.getPosition().x, 0);
	}
	else if (_sprite.getPosition().y + _sprite.getTexture()->getSize().y < 0)
	{
		_sprite.setPosition(_sprite.getPosition().x, windowSize.y);
		_hitbox.setPosition(_hitbox.getPosition().x, windowSize.y);
	}
}

sf::Vector2f Entity::GetPosition() const
{
	return _sprite.getPosition();
}

void Entity::Update(const float& dt, sf::Vector2u windowSize)
{
}

void Entity::Render(sf::RenderTarget* _target)
{
	_target->draw(_sprite);

	_target->draw(_hitbox);
}

