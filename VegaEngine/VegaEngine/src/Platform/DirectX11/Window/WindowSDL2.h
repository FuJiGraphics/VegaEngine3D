#pragma once
#include "Defines.h"

// SDL
struct SDL_Window;
struct SDL_Surface;

namespace vega {

	class IWindow;
	struct WindowSpec;

	class WindowSDL2 : public IWindow
	{
	public:
		WindowSDL2(const WindowSpec& spec);
		virtual ~WindowSDL2();

		void Init() final;
		void Release() final;
		void PollEvent() final;
		void Frame() final;

		inline unsigned int GetWidth() const final { return m_Width; }
		inline unsigned int GetHeight() const final { return m_Height; }
		inline std::string GetTitle() const final { return m_Title; }

		void SetEventCallback(const EventCallbackFn& callback) final;

	private:
		unsigned int m_Width;
		unsigned int m_Height;
		std::string m_Title;
		bool m_IsFullscreen;
		bool m_IsReleased;

		EventCallbackFn	m_EventCallbackFunc;
		SDL_Window* m_pWindow;
		SDL_Surface* m_pSurface;
	};

} // namespace vega
