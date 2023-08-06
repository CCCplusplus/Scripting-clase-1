#pragma once
#include "Scene.h"
#include "GameEngine.h"
#include "Button.h"
class Menu : public Scene
{
private:
	sf::RectangleShape _rect;
	sf::Font _font;
	sf::Texture BackgroundI;

	std::map<std::string, GUI::Button*> buttons;

	void InitBackground();
	void InitFont();
	void InitButton();
	void InitBGTexture();



protected:
	void InitKeys();

public:
	Menu(sf::RenderWindow* _target, std::map<std::string, int>* _supportKeys,
		std::stack<Scene*>* _scenes);

	virtual ~Menu();

	void Update(const float& dt);

	void UpdateButtons(const float& dt);



	void Render(sf::RenderTarget* _target);
};

