#include "pch.h"
#include "PlayerBullets.h"

PlayerBullets::PlayerBullets(sf::Texture& _texture, Player* player)
    : Bullets(_texture, player->GetPosition().x, player->GetPosition().y, 10), playerInstance(player)
{
    if (player->State())
    {
        moveSpeed = abs(moveSpeed); 
    }
    else
    {
        moveSpeed = -abs(moveSpeed); 
    }
}

void PlayerBullets::Update(const float& dt, sf::Vector2u windowSize)
{
    
    Move(moveSpeed * dt, 0, dt, windowSize);

    lifeTime += dt;
    if (lifeTime >= 3.0f)
    {
        Die();
        return;
    }
    
}

void PlayerBullets::HandleCollision(Entity* otherEntity)
{
    if (otherEntity == playerInstance) 
        return;
    
    if (!otherEntity || otherEntity == this || dynamic_cast<Bullets*>(otherEntity))
        return;

    otherEntity->TakeDamage(damage); // Dañar la otra entidad
    this->hp = 0; //morirnos a lo vorgo :3
    
}

