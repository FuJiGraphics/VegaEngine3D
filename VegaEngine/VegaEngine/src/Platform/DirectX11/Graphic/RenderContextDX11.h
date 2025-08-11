#pragma once

namespace vega {

	class RenderContextDX11 final : public IRenderContext
	{
	public:
		RenderContextDX11();
		virtual ~RenderContextDX11();

		void Init(const IWindow& window) final;
		void Release() final;

		void Init_ImGui() final;
		void Release_ImGui() final;

		void Render() final;
		void Present() final;

	private:

		void CreateRenderTargetView();
		void CreateDeviceAndSwapChain(HWND hwnd);
		void CleanupRenderTargetView();
		void CleanupDeviceAndSwapChain();

	private:
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;
		IDXGISwapChain* m_pSwapChain;
		ID3D11RenderTargetView* m_pRenderTargetView;
	};

} // namespace vega
