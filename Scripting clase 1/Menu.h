#pragma once
#include "Scene.h"
#include "GameEngine.h"
class Menu : public Scene
{
private:
	sf::RectangleShape _rect;

	GameEngine States;

protected:
	void InitKeys();

public:
	Menu(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys);

	virtual ~Menu();

	void Update(const float& dt);

	void Render(sf::RenderTarget* _target);
};

