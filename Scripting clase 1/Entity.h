#pragma once
class Entity
{
private:

protected:
	float moveSpeed;

	sf::RectangleShape rect;

public:
	Entity();

	~Entity();

	void InitSpirte();

	void InitMovement();

	void InitHitBox();

	virtual void SetPosition(const float x, const float y);

	virtual void Move(const float x, const float y, const float& dt);

	virtual void Update(const float& dt);

	void Render(sf::RenderTarget* _target);
};

