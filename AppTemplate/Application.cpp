#include "Application.h"

void Application::run(unsigned int w, unsigned int h)
{
	m_ScreenWidth = w;
	m_ScreenHeight = h;
	m_Window.create(VideoMode(m_ScreenWidth, m_ScreenHeight), "Paths", Style::Close);
	m_Running = true;

	m_Clock.restart();

	m_Canvas.init(&m_Window);



	while (m_Running)
	{
		Time delta = m_Clock.restart();
		handleInput();
		update(delta);
		render();
	}
}

void Application::handleInput()
{
	Event evt;
	while (m_Window.pollEvent(evt))
	{
		switch (evt.type)
		{
		case Event::LostFocus:
			m_Canvas.setFocus(false);
			break;
		case Event::GainedFocus:
			m_Canvas.setFocus(true);
			break;
		case Event::Closed:
			m_Running = false;
			break;
		case Event::KeyPressed:
			m_Canvas.handleKbdEvent(evt.key.code, true);
			break;
		case Event::KeyReleased:
			m_Canvas.handleKbdEvent(evt.key.code, false);
			break;
		case Event::MouseButtonPressed:
			m_Canvas.handleMouseEvent(evt.mouseButton.button, true);
			break;
		case Event::MouseButtonReleased:
			m_Canvas.handleMouseEvent(evt.mouseButton.button, false);
			break;
		default:
			break;
		}
	}
}

void Application::update(Time delta)
{
	m_Canvas.update(delta);
}

void Application::render()
{
	m_Window.clear(Color::Black);

	m_Window.draw(m_Canvas);

	m_Window.display();
}
