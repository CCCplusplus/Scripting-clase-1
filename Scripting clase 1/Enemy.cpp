#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(sf::Texture& _texture, const float X, const float Y, Player* player)
{
	InitSpirte(_texture);

	SetPosition(X, Y);

	moveSpeed = 150;

	_player = player; //guarda el apuntador al jugador

	
}

Enemy::~Enemy()
{
}


void Enemy::SetObjective()
{
	sf::Vector2f playerPos = _player->GetPosition();
}

void Enemy::MovetoObjective(const float& dt, sf::Vector2u windowSize)
{
	//calculamos a donde tenemos que ir 
	sf::Vector2f direction = _player->GetPosition() - GetPosition();
	float Limit = 400;
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);

    //se supone que esto es para "normalizar"
	direction /= length;

	// muevete en la direccion del jugador
	if (length >= Limit) {
		Move(direction.x, direction.y, dt, windowSize);
	}
}

void Enemy::Update(const float& dt, sf::Vector2u windowSize)
{
	SetObjective();
	MovetoObjective(dt, windowSize);
}
