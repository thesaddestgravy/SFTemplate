#include "UIString.h"

void UIString::create(std::string text)
{
	m_Font.loadFromFile("res/IBM.ttf");	
	m_Text.setFont(m_Font);
	m_Text.setString(text);
	m_Text.setCharacterSize(18);
	m_Text.setOutlineThickness(3.f);
}

void UIString::setPosition(Vec2 pos)
{
	m_Text.setPosition(Vec2(pos.x - m_Text.getGlobalBounds().width / 2, pos.y - m_Text.getGlobalBounds().height / 2 - m_Text.getLocalBounds().top));
}

void UIString::setColor(Color c)
{
	m_Text.setFillColor(c);
}

void UIString::setString(std::string text)
{
	m_Text.setString(text);
}

void UIString::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_Text);
}
