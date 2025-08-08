#include "pch.h"
#include "Input.h"
#include "InputWindows.h"

namespace vega {

	Unique<Input> Input::s_Instance = nullptr;

	void Input::Init(EInputDevice device)
	{
		switch (device) 
		{
			case EInputDevice::Windows: 
				s_Instance = CreateUnique<InputWindows>();
				break;
		}
	}

} // namespace vega
