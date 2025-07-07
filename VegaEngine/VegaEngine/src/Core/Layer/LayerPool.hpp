#pragma once
#include "LayerPool.h"

namespace vega {

	template<typename T, typename ...Args>
	inline T* LayerPool::Take(Args && ...args)
	{
		// if (unused.size() > size)
		// {
		// 	// ������ ������Ʈ Ǯ������ Ŭ ��� ���� ó��
		// 	return nullptr;
		// }
		if (unused.empty())
		{
			T* obj = new T(std::forward<Args>(args)...);
			unused.push_back(obj);
		}
		T* ret = (T*)unused.front();
		unused.pop_front();
		used.push_back(ret);
		return ret;
	}

	template<typename T>
	inline void LayerPool::Return(T* obj)
	{
		auto it = std::find(used.begin(), used.end(), obj);
		if (it != used.end())
		{
			used.erase(it);
			unused.push_back(obj);
		}
		else
		{
			// ������Ʈ Ǯ�� ���� ��� ���� ó��
			return;
		}
	}

} // namespace vega