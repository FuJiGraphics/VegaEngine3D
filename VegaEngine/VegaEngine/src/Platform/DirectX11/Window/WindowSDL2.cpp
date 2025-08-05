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
		, m_RepeatOn(false)
		, m_RepeatCount(0)
		, m_EventHandlerMap()
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
		
		// Create window
		m_pWindow = SDL_CreateWindow(
			m_Title.c_str(),
			SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, 
			static_cast<int>(m_Width), 
			static_cast<int>(m_Height), 
			SDL_WINDOW_SHOWN
		);

		FZLOG_ASSERT(m_pWindow, "Window could not be created! SDL_Error: {0}", SDL_GetError());


		// Get window surface
		m_pSurface = SDL_GetWindowSurface(m_pWindow);

		// Fill the surface white
		SDL_FillRect(m_pSurface, NULL, SDL_MapRGB(m_pSurface->format, 0xFF, 0xFF, 0xFF));

		//SDL TypeConvert Init
		TypeConverter::Init();

		// Init EventHandler
		InitEventHandler();
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
			if (m_EventHandlerMap.contains(event.type))
			{
				m_EventHandlerMap[event.type](event);
			}
		}
	}

	void WindowSDL2::Frame()
	{
		SDL_UpdateWindowSurface(m_pWindow);
	}

	void WindowSDL2::InitEventHandler()
	{
		// Window Close Event
		m_EventHandlerMap[SDL_QUIT] = [this](SDL_Event& e){
			if (m_EventCallbackFunc != nullptr)
			{
				WindowCloseEvent ev;
				m_EventCallbackFunc(ev);
			}
		};

		// Keyboard KeyDown Event
		m_EventHandlerMap[SDL_KEYDOWN] = [this](SDL_Event& e) {
			if (m_EventCallbackFunc != nullptr)
			{
				if (m_RepeatOn == false)
				{
					m_RepeatOn = true;
					m_RepeatCount = 0;
				}
				else
					m_RepeatCount++;
				KeyPressedEvent ev(TypeConverter::ToVegaKeyType(e.key.keysym.sym), m_RepeatCount);
				m_EventCallbackFunc(ev);
			}
		};

		// Keyboard KeyUp Event
		m_EventHandlerMap[SDL_KEYUP] = [this](SDL_Event& e) {
			if (m_EventCallbackFunc != nullptr)
			{
				m_RepeatOn = false;
				m_RepeatCount = 0;
				KeyReleasedEvent ev(TypeConverter::ToVegaKeyType(e.key.keysym.sym));
				m_EventCallbackFunc(ev);
			}
		};

		// Keyboard Mouse Button Down Event
		m_EventHandlerMap[SDL_MOUSEBUTTONDOWN] = [this](SDL_Event& e) {
			if (m_EventCallbackFunc != nullptr)
			{
				MouseButtonPressedEvent ev(TypeConverter::ToVegaMouseButtonType(e.button.button));
				m_EventCallbackFunc(ev);
			}
		};

		// Keyboard Mouse Button Up Event
		m_EventHandlerMap[SDL_MOUSEBUTTONUP] = [this](SDL_Event& e) {
			if (m_EventCallbackFunc != nullptr)
			{
				MouseButtonReleasedEvent ev(TypeConverter::ToVegaMouseButtonType(e.button.button));
				m_EventCallbackFunc(ev);
			}
		};

		// Keyboard Mouse Moved Event
		m_EventHandlerMap[SDL_MOUSEMOTION] = [this](SDL_Event& e) {
			if (m_EventCallbackFunc != nullptr)
			{
				MouseMovedEvent ev(e.button.x, e.button.y);
				m_EventCallbackFunc(ev);
			}
		};
	}

	void WindowSDL2::SetEventCallback(const EventCallbackFn& callback)
	{
		m_EventCallbackFunc = callback;
	}

} // namespace vega