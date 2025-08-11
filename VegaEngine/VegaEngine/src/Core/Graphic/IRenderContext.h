#pragma once

namespace vega {

	class IWindow;
	class IRenderContext;

	enum class GraphicsAPI
	{
		DirectX11,
	};

	struct RenderSpec
	{
		GraphicsAPI Api;
	};

	class IRenderContext
	{
	public:
		static Shared<IRenderContext> Create(const RenderSpec& spec);

		virtual void Init(const IWindow& window) = 0;
		virtual void Release() = 0;

		virtual void Init_ImGui() = 0;
		virtual void Release_ImGui() = 0;

		virtual void Render() = 0;
		virtual void Present() = 0;

	protected:
		IRenderContext(IRenderContext&) = delete;
		IRenderContext& operator=(IRenderContext&) = delete;

		IRenderContext() = default;
		virtual ~IRenderContext() = default;
	};

} // namespace vega