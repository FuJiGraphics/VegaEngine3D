#pragma once
#include "Defines.h"
#include <windows.h>

namespace vega {

	class Window;
	struct WindowSpec;
	class Input;
	class Application;

	class WindowSDL2 : public Window
	{
	public:
		WindowSDL2(const WindowSpec& spec);
		virtual ~WindowSDL2();

		bool Init() final;
		void Release() final;
		void Frame(bool& isRunning) final;

		inline unsigned int GetWidth() const final;
		inline unsigned int GetHeight() const final;
		inline const std::string& GetTitle() const final;

	private:
		void InitWindow();
		void ReleaseWindow();

	private:
		unsigned int m_Width;
		unsigned int m_Height;
		std::string m_Title;
		bool m_IsFullscreen;
		bool m_IsReleased;

		Input* m_Input;
		Application* m_Application;

		HINSTANCE m_Hinstance;
		HWND m_Hwnd;
	};

} // namespace vega
