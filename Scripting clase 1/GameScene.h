#pragma once
#include "Scene.h"
#include "Player.h"
#include "GameEngine.h"
class GameScene : public Scene
{
private:
	//Player Jugador;

	GameEngine States;

	sf::RectangleShape _rect;

protected:

	void InitKeys();


public:
	GameScene(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys);

	virtual ~GameScene();

	void Update(const float& dt);

	void Render(sf::RenderTarget* _target);
};

