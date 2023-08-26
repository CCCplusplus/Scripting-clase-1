#include "pch.h"
#include "EnemyBullets.h"
#include "Enemy.h"

EnemyBullets::EnemyBullets(sf::Texture& _texture, Enemy* enemy, Player* player)
    : Bullets(_texture, enemy->GetPosition().x, enemy->GetPosition().y, 10), enemyInstance(enemy)
{
    targetDirection = player->GetPosition() - enemy->GetPosition();
    float length = sqrt(targetDirection.x * targetDirection.x + targetDirection.y * targetDirection.y);
    targetDirection /= length;
    isActive = true;
}

void EnemyBullets::Update(const float& dt, sf::Vector2u windowSize)
{

    Move(targetDirection.x * moveSpeed * dt, targetDirection.y * moveSpeed * dt, dt, windowSize);

    lifeTime += dt;
    if (lifeTime >= 3.0f)
    {
        Die();
        return;
    }
}

void EnemyBullets::HandleCollision(Entity* otherEntity)
{
    if (otherEntity == enemyInstance) 
        return;

    if (!otherEntity || otherEntity == this || dynamic_cast<Bullets*>(otherEntity))
        return;

    otherEntity->TakeDamage(damage); 
    this->hp = 0;
}
