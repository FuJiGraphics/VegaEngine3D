#include "pch.h"
#include "Input.h"

namespace vega {

	void Input::Init()
	{
		for (int i = 0; i < 256; ++i)
		{
			m_Keys[i] = false;
		}
	}

	void Input::KeyDown(unsigned int key)
	{
		FZLOG_INFO("{0} KeyDown", key);
		m_Keys[key] = true;
	}

	void Input::KeyUp(unsigned int key)
	{
		FZLOG_INFO("{0} KeyUp", key);
		m_Keys[key] = false;
	}

	bool Input::IsKeyDown(unsigned int key)
	{
		FZLOG_INFO("{0} KeyClick", key);
		return m_Keys[key];
	}

} // namespace vega
