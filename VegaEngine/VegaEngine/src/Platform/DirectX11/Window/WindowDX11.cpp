#include "pch.h"
#include "Core/Window.h"
#include "WindowDX11.h"
#include "Input.h"
#include "Application.h"

namespace vega {

	WindowDX11::WindowDX11(const WindowSpec& spec)
		: m_Width(spec.Width)
		, m_Height(spec.Height)
		, m_Title(spec.Title)
		, m_IsFullscreen(spec.Fullscreen)
		, m_IsReleased(false)
		, m_Input(nullptr)
		, m_Application(nullptr)
		, m_Hinstance(NULL)
		, m_Hwnd(NULL)
	{
		// Empty
	}

	WindowDX11::~WindowDX11()
	{
		FZLOG_ASSERT(m_IsReleased, "Window was not properly released.");
	}

	bool WindowDX11::Init()
	{
		bool result;

		InitWindow();

		// Create and initialize the input object.  
		// This object will be used to handle reading the keyboard input from the user.
		m_Input = new Input();
		m_Input->Init();

		m_Application = new Application();
		result = m_Application->Initialize(m_Width, m_Height, m_Hwnd);
		if (!result)
		{
			return false;
		}

		s_TargetHandler = this;
		return true;
	}

	void WindowDX11::Release()
	{
		// Release the application class object.
		m_Application->Shutdown();
		VG_RELEASE_PTR(m_Application);

		// Release the input object.
		VG_RELEASE_PTR(m_Input);

		// Shutdown the window.
		ReleaseWindow();

		// Set WindowHandler null
		s_TargetHandler = nullptr;

		m_IsReleased = true;
		return;
	}

	void WindowDX11::Frame(bool& isRunning)
	{
		MSG msg = {};
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) 
			{
				isRunning = false;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	inline unsigned int WindowDX11::GetWidth() const
	{
		return m_Width;
	}

	inline unsigned int WindowDX11::GetHeight() const
	{
		return m_Height;
	}

	inline const std::string& WindowDX11::GetTitle() const
	{
		return m_Title;
	}

	LRESULT WindowDX11::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
	{
		switch (umsg)
		{
			case WM_KEYDOWN:
			{
				m_Input->KeyDown((unsigned int)wparam);
				return 0;
			}
			case WM_KEYUP:
			{
				m_Input->KeyUp((unsigned int)wparam);
				return 0;
			}
			default:
			{
				return DefWindowProc(hwnd, umsg, wparam, lparam);
			}
		}
	}

	void WindowDX11::InitWindow()
	{
		WNDCLASSEX wc = {};
		DEVMODE dmScreenSettings = {};
		int posX = 0, posY = 0;

		m_Hinstance = GetModuleHandle(nullptr);

		std::wstring widestr(m_Title.begin(), m_Title.end());
		const wchar_t* wTitle = widestr.c_str();

		// 윈도우 클래스 설정
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.hInstance = m_Hinstance;
		wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszClassName = wTitle;

		RegisterClassEx(&wc);

		DWORD style = 0;
		DWORD exStyle = WS_EX_APPWINDOW;

		if (m_IsFullscreen)
		{
			style = WS_POPUP;

			m_Width = GetSystemMetrics(SM_CXSCREEN);
			m_Height = GetSystemMetrics(SM_CYSCREEN);

			dmScreenSettings.dmSize = sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth = m_Width;
			dmScreenSettings.dmPelsHeight = m_Height;
			dmScreenSettings.dmBitsPerPel = 32;
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

			posX = posY = 0;
		}
		else
		{
			style = WS_OVERLAPPEDWINDOW;

			posX = (GetSystemMetrics(SM_CXSCREEN) - m_Width) / 2;
			posY = (GetSystemMetrics(SM_CYSCREEN) - m_Height) / 2;
		}

		m_Hwnd = CreateWindowEx(
			exStyle,
			wTitle,
			wTitle,
			style,
			posX,
			posY,
			m_Width,
			m_Height,
			nullptr,
			nullptr,
			m_Hinstance,
			nullptr
		);

		ShowWindow(m_Hwnd, SW_SHOW);
		SetForegroundWindow(m_Hwnd);
		SetFocus(m_Hwnd);
		ShowCursor(false);
	}

	void WindowDX11::ReleaseWindow()
	{
		// Show the mouse cursor.
		ShowCursor(true);

		// Fix the display settings if leaving full screen mode.
		if (m_IsFullscreen)
		{
			ChangeDisplaySettings(NULL, 0);
		}

		// Remove the window.
		DestroyWindow(m_Hwnd);
		m_Hwnd = NULL;

		// Remove the application instance.
		std::wstring widestr = std::wstring(m_Title.begin(), m_Title.end());
		const wchar_t* wTitle = widestr.c_str();
		UnregisterClass(wTitle, m_Hinstance);
		m_Hinstance = NULL;

		return;
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
	{
		switch (uMsg)
		{
			// Check if the window is being destroyed.
			case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}

			// Check if the window is being closed.
			case WM_CLOSE:
			{
				PostQuitMessage(0);
				return 0;
			}

			// All other messages pass to the message handler in the system class.
			default:
			{
				return WindowDX11::s_TargetHandler->MessageHandler(hwnd, uMsg, wparam, lparam);
			}
		}
	}

} // namespace vega
