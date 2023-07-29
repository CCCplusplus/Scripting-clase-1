#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(const float X, const float Y, Player* player)
{
	InitSpirte(100, 100, sf::Color::White);

	SetPosition(X, Y);

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
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);

    //se supone que esto es para "normalizar"
	direction /= length;

	// muevete en la direccion del jugador
	Move(direction.x, direction.y, dt, windowSize);
}

void Enemy::Update(const float& dt, sf::Vector2u windowSize)
{
	SetObjective();
	MovetoObjective(dt, windowSize);
}
