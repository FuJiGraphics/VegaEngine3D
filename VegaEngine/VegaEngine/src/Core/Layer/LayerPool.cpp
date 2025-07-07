#include "pch.h"
#include "LayerPool.h"
#include "Layer.h"

namespace vega {

	LayerPool::LayerPool(int initSize)
		: size(initSize)
	{
		// Empty
	}

	LayerPool::~LayerPool()
	{
		for (Layer* obj : unused)
		{
			delete obj;
		}
		for (Layer* obj : used)
		{
			delete obj;
		}
	}

} // namespace vega