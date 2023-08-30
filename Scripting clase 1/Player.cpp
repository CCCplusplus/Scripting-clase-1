#include "pch.h"
#include "Player.h"

Player::Player(sf::Texture& _texture, const float X, const float Y)
{
	InitSpirte(_texture);

	SetPosition(X, Y);

	moveSpeed = 200;

    hp = 200;

	facingRight = true;

    _sprite.setOrigin(_sprite.getTexture()->getSize().x / 2.0f, _sprite.getTexture()->getSize().y / 2.0f);

    BulletT.loadFromFile("Hadouken.png");
}


Player::~Player()
{
}

void Player::Flip()
{
    if (facingRight)
    {
        _sprite.setScale(-1.0f, 1.0f);
        
        facingRight = false;
    }
    else
    {
        _sprite.setScale(1.0f, 1.0f);
        
        facingRight = true;
    }
}


bool Player::State()
{
    if(facingRight)
    return true;
    else { return false; }
}

int Player::GetHP()
{
    return hp;
}

void Player::Dispara()
{
    gameboy->AddPBullet();
}

