#pragma once
#include "Defines.h"
#include <windows.h>

namespace vega {
	
	class Window;
	struct WindowSpec;
	class Input;
	class Application;

	class WindowDX11 : public Window
	{
	public:
		WindowDX11(const WindowSpec& spec);
		virtual ~WindowDX11();

		bool Init() final;
		void Release() final;
		void Frame(bool& isRunning) final;

		inline unsigned int GetWidth() const final;
		inline unsigned int GetHeight() const final;
		inline const std::string& GetTitle() const final;

		LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

	private:
		void InitWindow();
		void ReleaseWindow();

	public:
		inline static WindowDX11* s_TargetHandler = nullptr;

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

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

} // namespace vega
