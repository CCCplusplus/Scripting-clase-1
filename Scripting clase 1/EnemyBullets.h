#pragma once
#include "Bullets.h"
#include "Player.h"
#include "Enemy.h"

class Enemy;

class EnemyBullets : public Bullets
{
private:
    Enemy* enemyInstance; // Referencia al enemigo para evitar colisiones
    sf::Vector2f targetDirection; // Dirección hacia la posición del jugador

public:
    EnemyBullets(sf::Texture& _texture, Enemy* enemy, Player* player);

    void Update(const float& dt, sf::Vector2u windowSize) override;
    void HandleCollision(Entity* otherEntity) override;
};


