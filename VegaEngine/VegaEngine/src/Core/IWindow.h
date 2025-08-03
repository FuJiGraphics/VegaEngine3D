#pragma once

namespace vega {

	enum class WindowAPI
	{
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

	class IWindow
	{
	public:
		static Shared<IWindow> Create(const WindowSpec& spec);

		virtual void Init() = 0;
		virtual void Release() = 0;
		virtual void PollEvent() = 0;
		virtual void Frame() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual std::string GetTitle() const = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

	protected:
		IWindow(IWindow&) = delete;
		IWindow& operator=(IWindow&) = delete;

		IWindow() = default;
		virtual ~IWindow() = default;
	};

} // namespace vega