#pragma once
#include "Defines.h"

namespace vega {

	class Window;
	class LayerContainer;

	class System
	{
	public:
		System(int width, int height, const std::string& title);
		virtual ~System() = default;

		void Init();
		void Release();
		void Run();

		inline bool IsRunning() const { return m_IsRunning; }

	private:
		bool m_IsRunning = true;

		Shared<Window> m_Window;
		// Shared<LayerContainer> m_LayerContainer;
	};

	System* CreateSystem();

} // namespace vega
