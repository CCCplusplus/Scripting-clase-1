#include "pch.h"
#include "Bullets.h"

Bullets::Bullets(sf::Texture& _texture, const float X, const float Y, int damageValue)
{
    InitSpirte(_texture);
    SetPosition(X, Y);
    _sprite.setOrigin(_sprite.getTexture()->getSize().x / 2.0f, _sprite.getTexture()->getSize().y / 2.0f);
    damage = damageValue;
    walkX = 20;
    walkY = 0.0f;
    moveSpeed = 20; //tentativo
    lifeTime = 0.0f;
}

Bullets::~Bullets()
{
}

void Bullets::Update(const float& dt, sf::Vector2u windowSize)
{
    if (isActive)
    {
        Move(walkX, walkY, dt, windowSize);

        lifeTime += dt;
        if (lifeTime >= 3.0f) // Desactivar bala después de 3 segundos
        {
            isActive = false;
        }
    }
}


void Bullets::HandleCollision(Entity* otherEntity)
{
    if (otherEntity == owner) return; // Ignorar colisión con el propietario

    if (_hitboxInstance._hitbox.getGlobalBounds().intersects(otherEntity->_hitboxInstance._hitbox.getGlobalBounds()))
    {
        otherEntity->TakeDamage(damage);
        isActive = false; // Desactivar la bala después de colisionar
    }
}

void Bullets::activate(Entity* _owner)
{
    isActive = true;
    owner = _owner;
}

float Bullets::GetMoveSpeedX() const {
    return walkX;
}

void Bullets::SetMoveSpeedX(float newSpeed) {
    walkX = newSpeed;
}

float Bullets::GetMoveSpeedY() const {
    return walkY;
}

void Bullets::SetMoveSpeedY(float speed) {
    walkY = speed;
}

int Bullets::GetDamageValue() const
{
    return damage;
}
