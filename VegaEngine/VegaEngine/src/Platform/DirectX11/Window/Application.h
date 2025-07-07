#pragma once

namespace vega {

	class Application
	{
	public:
		Application();
		Application(const Application&);
		~Application();

		bool Initialize(int, int, HWND);
		void Shutdown();
		bool Frame();

	private:
		bool Render();

	private:

	};

} // namespace vega
