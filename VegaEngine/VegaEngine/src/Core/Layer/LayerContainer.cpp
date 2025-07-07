#include "pch.h"
#include "LayerPool.h"
#include "LayerContainer.h"
#include "Layer.h"

namespace vega {

	LayerContainer::LayerContainer(Shared<LayerPool>& linkPool)
		: m_Layers()
		, m_InsertIndex(0)
		, m_Pool(linkPool)
	{
		// Empty
	}

	LayerContainer::~LayerContainer()
	{
		this->Release();
	}

	void LayerContainer::Release()
	{
		if (m_Layers.empty())
			return;

		for (Layer* layer : m_Layers)
		{
			if (layer != nullptr)
			{
				layer->OnDetach();
				m_Pool->Return(layer);
			}
		}
		m_Layers.clear();
	}

	void LayerContainer::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer);
		m_InsertIndex++;
		layer->OnAttach();
	}

	void LayerContainer::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerContainer::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_InsertIndex, layer);
		if (it != m_Layers.begin() + m_InsertIndex)
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_InsertIndex--;
			m_Pool->Return(layer);
		}
	}

	void LayerContainer::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin() + m_InsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			overlay->OnDetach();
			m_Layers.erase(it);
			m_Pool->Return(overlay);
		}
	}

} // namespace vega