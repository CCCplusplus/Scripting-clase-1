#include "pch.h"
#include "pch.h"
#include "Hitbox.h"

Hitbox::Hitbox()
{
   
}

Hitbox::~Hitbox()
{
    
}

void Hitbox::Init(sf::Texture& texture, const sf::Vector2f& position)
{
    _hitbox.setSize(sf::Vector2f(texture.getSize().x, texture.getSize().y));
    _hitbox.setFillColor(sf::Color::Transparent);
    _hitbox.setPosition(position);


    // Debug: see the outline of the hitbox.
    _hitbox.setOutlineThickness(1.0f);
    _hitbox.setOutlineColor(sf::Color::Red);
}

void Hitbox::Follow(const sf::Sprite& sprite, const float x, const float y, const float& dt, sf::Vector2u windowSize)
{

    _hitbox.setPosition(sprite.getPosition());

    // Adjust position based on screen bounds
    if (_hitbox.getPosition().x > windowSize.x)
    {
        _hitbox.setPosition(0, _hitbox.getPosition().y);
    }
    else if (_hitbox.getPosition().x + _hitbox.getSize().x < 0)
    {
        _hitbox.setPosition(windowSize.x, _hitbox.getPosition().y);
    }
    if (_hitbox.getPosition().y > windowSize.y)
    {
        _hitbox.setPosition(_hitbox.getPosition().x, 0);
    }
    else if (_hitbox.getPosition().y + _hitbox.getSize().y < 0)
    {
        _hitbox.setPosition(_hitbox.getPosition().x, windowSize.y);
    }
}

void Hitbox::Render(sf::RenderTarget* _target)
{
    _target->draw(_hitbox);
}

