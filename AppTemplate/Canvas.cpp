#include "Canvas.h"

void Canvas::init(RenderWindow* wnd)
{
	m_Window = wnd;
	m_Timer.restart();
}

void Canvas::handleKbdEvent(Keyboard::Key k, bool pressed)
{

}

void Canvas::handleMouseEvent(Mouse::Button b, bool pressed)
{

}

void Canvas::update(Time delta)
{

}

void Canvas::setFocus(bool focus)
{
	m_Focus = focus;
}

void Canvas::draw(RenderTarget& target, RenderStates states) const
{

}
