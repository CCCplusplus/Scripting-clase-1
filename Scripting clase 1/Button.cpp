#include "pch.h"
#include "Button.h"

GUI::Button::Button(float x, float y, float width, float height, sf::Font* _font, std::string _text, unsigned _fontSize, sf::Color _idleText, sf::Color _hoverText, sf::Color _pressText, sf::Color _idleColor, sf::Color _hoverColor, sf::Color _pressColor, short unsigned id)
{
    buttonState = BTN_IDDLE;
    this->id = id;

    rect.setPosition(x, y);
    rect.setSize(sf::Vector2f(width, height));

    this->idleText = _idleText;
    this->hoverText = _hoverText;
    this->pressText = _pressText;

    this->font = _font;
    text.setFont(*font);
    text.setString(_text);
    text.setFillColor(idleText);
    text.setCharacterSize(_fontSize);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x + width / 2.0f, y + height / 2.0f));

    this->idleColor = _idleColor;
    this->hoverColor = _hoverColor;
    this->pressColor = _pressColor;

    rect.setFillColor(idleColor);
}

GUI::Button::~Button()
{
}

const std::string GUI::Button::GetText()
{
    return std::string();
}

const short unsigned& GUI::Button::GetID()
{
    // TODO: insert return statement here
    return 0;
}

void GUI::Button::SetText(const std::string text)
{
}

void GUI::Button::SetID(const short unsigned id)
{
}

void GUI::Button::Update(const sf::Vector2f mousePos)
{
    //TODO:
    //definir los estados que debe de tener para idle, hover y press
}

void GUI::Button::Render(sf::RenderTarget* _target)
{
    _target->draw(rect);
    _target->draw(text);
}

const bool GUI::Button::GetButtonPress()
{
    return false;
}
