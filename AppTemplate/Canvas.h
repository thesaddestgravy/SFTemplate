#pragma once

#include "Backend.h"

class Canvas : public Drawable
{
public:
	void init(RenderWindow* wnd);

	void handleKbdEvent(Keyboard::Key k, bool pressed);
	void handleMouseEvent(Mouse::Button b, bool pressed);
	void update(Time delta);
	void setFocus(bool focus);
private:
	void draw(RenderTarget& target, RenderStates states) const;

	bool m_Focus;

	Clock m_Timer;

	RenderWindow* m_Window;
};