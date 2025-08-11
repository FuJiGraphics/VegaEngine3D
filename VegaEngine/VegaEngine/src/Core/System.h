#pragma once
#include "Defines.h"

namespace vega {

	class IWindow;
	class LayerContainer;
	class Event;
	class WindowCloseEvent;
	class IRenderContext;

	/**
	 * @brief Core system class that manages the game loop and window events.
	 */
	class System
	{
	public:
		/**
		 * @brief Construct a new System object.
		 *
		 * @param width The width of the window.
		 * @param height The height of the window.
		 * @param title The title of the window.
		 */
		System(int width, int height, const std::string& title);

		/**
		 * @brief Virtual destructor.
		 */
		virtual ~System() = default;

		/**
		 * @brief Initializes the system and its components.
		 */
		void Init();

		/**
		 * @brief Releases all allocated resources.
		 */
		void Release();

		/**
		 * @brief Runs a single frame of the system (update/render).
		 */
		void Frame();

		/**
		 * @brief Handles an incoming event.
		 *
		 * @param e The event to process.
		 */
		void OnEvent(vega::Event& e);

		/**
		 * @brief Handles window close events.
		 *
		 * @param e The window close event.
		 * @return true if the window should close.
		 * @return false to ignore the close event.
		 */
		bool OnWindowClose(WindowCloseEvent& e);

		/**
		 * @brief Checks whether the system is still running.
		 *
		 * @return true if the system is running.
		 * @return false if the system should exit.
		 */
		inline bool IsRunning() const { return m_IsRunning; }

		/**
		 * @brief Requests the system to exit.
		 */
		inline void ExitProgram() { m_IsRunning = false; }

	private:
		bool m_IsRunning = true;					///< Flag to control the main loop.
		Shared<IWindow> m_Window;					///< Main application window.
		Shared<LayerContainer> m_LayerContainer;	///< (Commented out) Layer management container.
		Shared<IRenderContext> m_RenderContext;		/// Rendering Context
	};

	/**
	 * @brief Factory function to create a System instance.
	 *
	 * @return Pointer to the created System object.
	 */
	System* CreateSystem();

} // namespace vega
