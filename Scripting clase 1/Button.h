#pragma once


enum BUTTONSTATES {BTN_IDDLE = 0,BTN_HOVER,BTS_PRESS};
namespace GUI 
{
	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape rect;
		sf::Font* font;
		sf::Text text;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color pressColor;

		sf::Color idleText;
		sf::Color hoverText;
		sf::Color pressText;
	public:
		Button(float x, float y, float width, float height,sf::Font* _font,std::string _text,
			unsigned _fontSize, sf::Color _idleText, sf::Color _hoverText, sf::Color _pressText,
			sf::Color _idleColor, sf::Color _hoverColor, sf::Color _pressColor, short unsigned id = -1);
		virtual ~Button();

		const std::string GetText();
		const short unsigned& GetID();

		void SetText(const std::string text);
		void SetID(const short unsigned id);

		void Update(const sf::Vector2f mousePos);
		void Render(sf::RenderTarget* _target);

		const bool GetButtonPress();

	};

}

