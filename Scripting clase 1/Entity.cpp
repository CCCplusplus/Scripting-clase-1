#include "pch.h"
#include "Entity.h"

Entity::Entity()
{
	moveSpeed = 50;
}

Entity::~Entity()
{
}

void Entity::InitSpirte()
{
	
	rect.setSize(sf::Vector2f(100, 100));
	rect.setFillColor(sf::Color::Red);
}

void Entity::SetPosition(const float x, const float y)
{
	rect.setPosition(sf::Vector2f(x, y));
}

void Entity::Move(const float x, const float y, const float& dt)
{
	float xvalue = 0;
	xvalue += x * moveSpeed * dt;
	float yvalue = 0;
	yvalue += y * moveSpeed * dt;

	rect.move(sf::Vector2f(xvalue, yvalue));
}

void Entity::Update(const float& dt)
{
}

void Entity::Render(sf::RenderTarget* _target)
{
	_target->draw(rect);
}

