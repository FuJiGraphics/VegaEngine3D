#pragma once

#include "Input.h"

namespace vega {

	class InputWindows : public Input
	{
	protected:
		virtual bool IsKeyDownImpl(KeyType type) final;
		virtual bool IsMouseClickedImpl(MouseButtonType type) final;
		virtual std::pair<int, int> GetMousePosImpl() final;
	};

}
