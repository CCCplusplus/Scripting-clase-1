#pragma once
#include "Entity.h"
#include "Hitbox.h"
class Bullets : public Entity
{
private:
    Entity* owner;

protected:
    int damage; 
    float lifeTime;
    float walkX;
    float walkY;
    int score;

public:
    
    Bullets(sf::Texture& _texture, const float X, const float Y, int damageValue);

    ~Bullets();

    void Update(const float& dt, sf::Vector2u windowSize) override;

    void HandleCollision(Entity* otherEntity);

    void activate(Entity* _owner);

    void Deactivate();

    float GetMoveSpeedX() const;

    void SetMoveSpeedX(float newSpeed);

    float GetMoveSpeedY() const;

    void SetMoveSpeedY(float speed);
    
    int GetDamageValue() const;
};

