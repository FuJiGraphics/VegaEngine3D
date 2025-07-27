#pragma once
#include "Defines.h"

namespace vega {

	class Event;

	/**
	 * @
	 */
	class Layer
	{
	protected:
		// Using
		using Super = vega::Layer;
		// Delete
		VG_DELETE_COPY(Layer)

	public:
		Layer(const std::string& name);
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float dt) {}
		virtual void OnEvent(vega::Event& ev) {}
		virtual void OnUI() {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string	m_DebugName;
	};

} // namespace vega