#pragma once

namespace vega {
	
	class Window;
	struct WindowSpec;

	class WindowWin32 : public Window
	{
	public:
		WindowWin32(const WindowSpec& spec);

		inline unsigned int GetWidth() const override;
		inline unsigned int GetHeight() const override;
		inline const std::string& GetTitle() const override;

	private:
		unsigned int m_Width;
		unsigned int m_Height;
		std::string m_Title;
	};


} // namespace vega
