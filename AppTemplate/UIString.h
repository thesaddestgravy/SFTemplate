#pragma once

#include "Backend.h"

#include <string>

class UIString : public Drawable
{
public:
	void create(std::string text);
	void setPosition(Vec2 pos);
	void setColor(Color c);
	void setString(std::string text);
private:
	virtual void draw(RenderTarget& target, RenderStates states) const;
	Text m_Text;
	Font m_Font;
};