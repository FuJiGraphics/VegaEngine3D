#pragma once
#include "Defines.h"

namespace vega {

	class Input
	{
	protected:
		VG_DELETE_COPY(Input)

	public:
		Input() = default;
		~Input() = default;

		void Init();

		void KeyDown(unsigned int key);
		void KeyUp(unsigned int key);

		bool IsKeyDown(unsigned int key);

	private:
		bool m_Keys[256];
	};

} // namespace vega
