#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(sf::Texture& _texture, const float X, const float Y, Player* player)
{
	InitSpirte(_texture);

	SetPosition(X, Y);

	moveSpeed = 150;

	hp = 120;

	_player = player; //guarda el apuntador al jugador

	_sprite.setOrigin(_sprite.getTexture()->getSize().x / 2.0f, _sprite.getTexture()->getSize().y / 2.0f);

	elapsedtime = 0;

	EnemyBulletT.loadFromFile("BlackHole.png");
}

Enemy::~Enemy()
{
}

void Enemy::SetObjective()
{
	sf::Vector2f playerPos = _player->GetPosition();
}

void Enemy::Dispara()
{
	gameSceneInstance->AddBullet();
}

void Enemy::Die()
{
	isActive = false;
}


void Enemy::MovetoObjective(const float& dt, sf::Vector2u windowSize)
{
	//calculamos a donde tenemos que ir 
	sf::Vector2f direction = _player->GetPosition() - GetPosition();
	float Limit = 600;
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);

    //se supone que esto es para "normalizar"
	direction /= length;

	// muevete en la direccion del jugador
	if (length >= Limit) {
		Move(direction.x, direction.y, dt, windowSize);
	}
	else 
	{
		if (elapsedtime <= 0) {
			std::cout << "Shootini \n";
			elapsedtime = 3;
			Dispara();
		}
	}
	elapsedtime -= dt;
}

void Enemy::Update(const float& dt, sf::Vector2u windowSize)
{
	if (hp <= 0)
		Die();
	
	SetObjective();
	MovetoObjective(dt, windowSize);
}
