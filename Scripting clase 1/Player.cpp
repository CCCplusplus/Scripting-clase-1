#include "pch.h"
#include "Player.h"

Player::Player(sf::Texture& _texture, const float X, const float Y)
{
	InitSpirte(_texture);

	SetPosition(X, Y);

	InitHitBox(_texture);
}


Player::~Player()
{
}

void Player::Update(const float& dt)
{

}
