#pragma once
#include <SFML/Graphics.hpp>

class Hitbox
{
private:
    

public:
    Hitbox();
    ~Hitbox();

    void Init(sf::Texture& texture, const sf::Vector2f& position);
    void Follow(const sf::Sprite& sprite, const float x, const float y, const float& dt, sf::Vector2u windowSize);
    void Render(sf::RenderTarget* _target);

    sf::RectangleShape _hitbox;
};



