#pragma once

#include "Canvas.h"

class Application
{
public:
	void run(unsigned int w, unsigned int h);
private:
	void handleInput();
	void update(Time delta);
	void render();

	bool m_Running;
	unsigned int m_ScreenWidth;
	unsigned int m_ScreenHeight;
	Clock m_Clock;

	RenderWindow m_Window;

	Canvas m_Canvas;
};