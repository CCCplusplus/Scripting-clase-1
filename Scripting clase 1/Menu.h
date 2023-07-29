#pragma once
#include "Scene.h"
#include "GameEngine.h"
#include "Button.h"
class Menu : public Scene
{
private:
	sf::RectangleShape _rect;
	sf::Font _font;

	GUI::Button* button1;
	GUI::Button* button2;
	GUI::Button* button3;

	void InitFont();
	void InitButton();


protected:
	void InitKeys();

public:
	Menu(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys,
		std::stack<Scene*>* _scenes);

	virtual ~Menu();

	void Update(const float& dt);

	void Render(sf::RenderTarget* _target);
};

