#pragma once
#include "Scene.h"
#include "GameEngine.h"
class Editor : public Scene
{
private:
	sf::RectangleShape _rect;

	GameEngine States;

protected:
	void InitKeys();

public:
	Editor(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys);

	virtual ~Editor();

	void Update(const float& dt);

	void Render(sf::RenderTarget* _target);
};

