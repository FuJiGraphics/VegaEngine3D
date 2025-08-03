#include "pch.h"

#include <SDL.h>

#include "Core/IWindow.h"
#include "WindowSDL2.h"

namespace vega {

	WindowSDL2::WindowSDL2(const WindowSpec& spec)
		: m_Width(spec.Width)
		, m_Height(spec.Height)
		, m_Title(spec.Title)
		, m_IsFullscreen(spec.Fullscreen)
		, m_IsReleased(false)
		, m_EventCallbackFunc(nullptr)
		, m_pWindow(nullptr)
		, m_pSurface(nullptr)
	{
		// Empty
	}

	WindowSDL2::~WindowSDL2()
	{
	}

	void WindowSDL2::Init()
	{

		FZLOG_ASSERT(SDL_Init(SDL_INIT_VIDEO) >= 0, 
					 "SDL could not initialize!SDL_Error: {0}", 
					 SDL_GetError());

		//Create window
		m_pWindow = SDL_CreateWindow(
			m_Title.c_str(),
			SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, 
			static_cast<int>(m_Width), 
			static_cast<int>(m_Height), 
			SDL_WINDOW_SHOWN
		);

		FZLOG_ASSERT(m_pWindow, "Window could not be created! SDL_Error: {0}", SDL_GetError());


		//Get window surface
		m_pSurface = SDL_GetWindowSurface(m_pWindow);

		//Fill the surface white
		SDL_FillRect(m_pSurface, NULL, SDL_MapRGB(m_pSurface->format, 0xFF, 0xFF, 0xFF));
	}

	void WindowSDL2::Release()
	{
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
	}

	void WindowSDL2::PollEvent()
	{
		if (m_EventCallbackFunc == nullptr)
			return;

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT: {
					WindowCloseEvent e;
					m_EventCallbackFunc(e);
				} break;
				case SDL_KEYDOWN: {
					KeyPressedEvent e(TypeConverter::ToVegaKeyType(event.key.keysym.sym));
					m_EventCallbackFunc(e);
				} break;
				case SDL_KEYUP: {
					KeyReleasedEvent e(TypeConverter::ToVegaKeyType(event.key.keysym.sym));
					m_EventCallbackFunc(e);
				} break;
				case SDL_MOUSEBUTTONDOWN: {
					MouseButtonPressedEvent e(TypeConverter::ToVegaMouseButtonType(event.button.type));
					m_EventCallbackFunc(e);
				} break;
				case SDL_MOUSEBUTTONUP: {
					MouseButtonReleasedEvent e(TypeConverter::ToVegaMouseButtonType(event.button.type));
					m_EventCallbackFunc(e);
				} break;
				case SDL_MOUSEMOTION: {
					MouseMovedEvent e(
						static_cast<int>(event.button.x), 
						static_cast<int>(event.button.y)
					);
					m_EventCallbackFunc(e);
				}
			}
		}

	}

	void WindowSDL2::Frame()
	{
		SDL_UpdateWindowSurface(m_pWindow);
	}

	void WindowSDL2::SetEventCallback(const EventCallbackFn& callback)
	{
		m_EventCallbackFunc = callback;
	}

} // namespace vega