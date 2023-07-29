#include "pch.h"
#include "Entity.h"

Entity::Entity()
{
	moveSpeed = 100;
}

Entity::~Entity()
{
}

void Entity::InitSpirte(float x, float y, sf::Color color)
{
	
	rect.setSize(sf::Vector2f(x, y));
	rect.setFillColor(color);
}

void Entity::SetPosition(const float x, const float y)
{
	rect.setPosition(sf::Vector2f(x, y));
}

void Entity::Move(const float x, const float y, const float& dt, sf::Vector2u windowSize)
{
	float xvalue = 0;
	xvalue += x * moveSpeed * dt;
	float yvalue = 0;
	yvalue += y * moveSpeed * dt;

	rect.move(sf::Vector2f(xvalue, yvalue));

	//Cuando un entity llegue a el limite de la pantalla se pasara al otro lado.
	if (rect.getPosition().x > windowSize.x)
	{
		rect.setPosition(0, rect.getPosition().y);
	}
	else if (rect.getPosition().x + rect.getSize().x < 0)
	{
		rect.setPosition(windowSize.x, rect.getPosition().y);
	}
	if (rect.getPosition().y > windowSize.y)
	{
		rect.setPosition(rect.getPosition().x, 0);
	}
	else if (rect.getPosition().y + rect.getSize().y < 0)
	{
		rect.setPosition(rect.getPosition().x, windowSize.y);
	}
}

sf::Vector2f Entity::GetPosition() const
{
	return rect.getPosition();
}

void Entity::Update(const float& dt, sf::Vector2u windowSize)
{
}

void Entity::Render(sf::RenderTarget* _target)
{
	_target->draw(rect);
}

