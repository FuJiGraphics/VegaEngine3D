#pragma once
#include "Defines.h"

namespace vega {

	class System
	{
	public:
		System(int width, int height, const std::string& title);

		void Init();
		void Release();
		void Run();

		inline bool IsRunning() const { return m_IsRunning; }

	private:
		bool m_IsRunning = true;

	};

} // namespace vega
