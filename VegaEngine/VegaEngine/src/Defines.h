#pragma once

/*
* @brief ���� ������, ���� ���� �����ڸ� �����մϴ�.
*/
#define VG_DELETE_COPY(ClassName)                       \
    ClassName(const ClassName&) = delete;               \
    ClassName& operator=(const ClassName&) = delete;


#define VG_RELEASE_PTR(ptr)                             \
    if((ptr) != nullptr)                                \
    {                                                   \
        delete ptr;                                     \
        ptr = nullptr;                                  \
    }

/**
 * @brief ��� �Լ� �����͸� std::bind�� �����Ͽ� Event �ݹ� �Լ� ��ü�� �����մϴ�.
 * @param[in] pfn ��� �Լ� ������ (��: &MyClass::OnEvent)
 * @return std::function<void(vega::Event&)> ���·� ��� ������ ���ε� �Լ� ��ü
 */
#define VG_BIND_CALLBACK_FN(pfn)                        \
    std::bind(&pfn, this, std::placeholders::_1)
