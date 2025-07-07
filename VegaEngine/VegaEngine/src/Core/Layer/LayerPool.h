#pragma once
#include <list>

namespace vega {

	class Layer;

	class LayerPool
	{
	private:
		std::list<Layer*> unused;
		std::list<Layer*> used;
		int size;

	public:
		LayerPool(int initSize = 100);
		virtual ~LayerPool();

		template <typename T, typename ...Args>
		T* Take(Args&&... args);

		template <typename T>
		void Return(T* obj);
	};

} // namespace vega

#include "LayerPool.hpp"