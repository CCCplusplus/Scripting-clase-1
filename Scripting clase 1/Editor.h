#pragma once
#include "Scene.h"
#include "GameEngine.h"
class Editor : public Scene
{
private:
	sf::RectangleShape _rect;



protected:
	void InitKeys();

public:
	Editor(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys,
		std::stack<Scene*>* _scenes);

	virtual ~Editor();

	void Update(const float& dt);

	void Render(sf::RenderTarget* _target);
};

