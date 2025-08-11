#include "pch.h"
#include "ImGuiManager.h"
#include "Core/IWindow.h"
#include "Core/Graphic/IRenderContext.h"

namespace vega {

	void ImGuiManager::Init(IWindow& window, IRenderContext& context)
	{
		float main_scale = ImGui_ImplSDL2_GetContentScaleForDisplay(0);
		
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	      // 도킹
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;		  // 멀티 뷰포트
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// Setup scaling
		ImGuiStyle& style = ImGui::GetStyle();
		style.ScaleAllSizes(main_scale);
		style.FontScaleDpi = main_scale;
		io.ConfigDpiScaleFonts = true;          // [Experimental] Automatically overwrite style.FontScaleDpi in Begin() when Monitor DPI changes. This will scale fonts but _NOT_ scale sizes/padding for now.
		io.ConfigDpiScaleViewports = true;      // [Experimental] Scale Dear ImGui and Platform Windows when Monitor DPI changes.

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		window.Init_ImGui();
		context.Init_ImGui();
	}

	void ImGuiManager::Release(IWindow& window, IRenderContext& context)
	{
		// Cleanup
		context.Release_ImGui();
		window.Release_ImGui();
		ImGui::DestroyContext();
	}

	void ImGuiManager::PollEvent(const SDL_Event& event)
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
	}

	void ImGuiManager::Frame()
	{
		// Start the Dear ImGui frame
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		// Our state
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


		ImGuiIO& io = ImGui::GetIO();
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}

		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}
	}

	bool ImGuiManager::IsFocusUI(const SDL_Event& event)
	{
		static const std::unordered_set<Uint32> mouseEvents = {
			SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONUP,
			SDL_MOUSEMOTION, SDL_MOUSEWHEEL
		};

		static const std::unordered_set<Uint32> keyboardEvents = {
			SDL_KEYDOWN, SDL_KEYUP, SDL_TEXTINPUT
		};

		const auto& io = ImGui::GetIO();

		if (io.WantCaptureMouse && mouseEvents.count(event.type))
			return true;

		if (io.WantCaptureKeyboard && keyboardEvents.count(event.type))
			return true;

		return false;
	}

} // namespace vega