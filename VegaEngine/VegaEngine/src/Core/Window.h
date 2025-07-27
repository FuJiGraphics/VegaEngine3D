#pragma once

namespace vega {

	enum class WindowAPI
	{
		Win32,
		SDL2,
	};

	struct WindowSpec
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		WindowAPI Api;
		bool Fullscreen;
		// bool VSync;
		// unsigned int AntialiasingLevel;
	};

	class Window
	{
	public:
		static Shared<Window> Create(const WindowSpec& spec);

		virtual bool Init() = 0;
		virtual void Release() = 0;
		virtual void Frame(bool& isRunning) = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual const std::string& GetTitle() const = 0;

	protected:
		Window(Window&) = delete;
		Window& operator=(Window&) = delete;

		Window() = default;
		virtual ~Window() = default;
	};

} // namespace vega