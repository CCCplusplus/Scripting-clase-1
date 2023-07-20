#include "pch.h"
#include "Button.h"

GUI::Button::Button(float x, float y, float width, float height, sf::Font* _font, std::string _text, unsigned _fontSize, sf::Color _idleText, sf::Color _hoverText, sf::Color _pressText, sf::Color _idleColor, sf::Color _hoverColor, sf::Color _pressColor, short unsigned id)
{
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
}

const bool GUI::Button::GetButtonPress()
{
    return false;
}
