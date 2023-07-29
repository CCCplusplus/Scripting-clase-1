#include "pch.h"
#include "Player.h"

Player::Player(const float X, const float Y)
{
	InitSpirte(100, 100, sf::Color::Red);

	SetPosition(X, Y);
}

Player::~Player()
{
}

void Player::Update(const float& dt)
{

}
