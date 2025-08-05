#pragma once
#include "Defines.h"

namespace vega {

	class IWindow;
	class LayerContainer;
	class Event;
	class WindowCloseEvent;

	class System
	{
	public:
		System(int width, int height, const std::string& title);
		virtual ~System() = default;

		void Init();
		void Release();
		void Frame();
		void OnEvent(vega::Event& e);

		bool OnWindowClose(WindowCloseEvent& e);

		inline bool IsRunning() const { return m_IsRunning; }
		inline void ExitProgram() { m_IsRunning = false; }

	private:
		bool m_IsRunning = true;

		Shared<IWindow> m_Window;
		// Shared<LayerContainer> m_LayerContainer;
	};

	System* CreateSystem();

} // namespace vega
