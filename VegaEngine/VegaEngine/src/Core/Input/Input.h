#pragma once

namespace vega {

	enum class EInputDevice
	{
		Windows
	};

	class Input 
	{
	public:
		static void Init(EInputDevice device);

		static bool IsKeyDown(KeyType type) { return s_Instance->IsKeyDownImpl(type); }
		static bool IsMouseClicked(MouseButtonType type) { return s_Instance->IsMouseClickedImpl(type); }
		static std::pair<int, int> GetMousePos() { return s_Instance->GetMousePosImpl(); }
		
	protected:
		virtual bool IsKeyDownImpl(KeyType type) = 0;
		virtual bool IsMouseClickedImpl(MouseButtonType type) = 0;
		virtual std::pair<int, int> GetMousePosImpl() = 0;

	private:
		static Unique<Input> s_Instance;
	};

} // namespace vega
