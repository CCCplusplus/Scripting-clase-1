#include "pch.h"
#include "Player.h"

Player::Player(sf::Texture& _texture, const float X, const float Y)
{
	InitSpirte(_texture);

	SetPosition(X, Y);

	moveSpeed = 200;

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

void Player::Dispara()
{
    Bullets* bullet = new Bullets(BulletT, GetPosition().x+20, GetPosition().y, 100);
    if (facingRight) {
        bullet->SetMoveSpeedX(abs(bullet->GetMoveSpeedX()));  // Asegura que sea positivo
    }
    else {
        bullet->SetMoveSpeedX(-abs(bullet->GetMoveSpeedX())); // Asegura que sea negativo
    }
    
    
    bullet->activate(this); // Establece al jugador como el propietario de la bala
    gameboy->AddPBullet(bullet);
}

