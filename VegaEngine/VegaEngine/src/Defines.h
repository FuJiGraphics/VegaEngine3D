#pragma once

/*
* @brief 복사 생성자, 복사 대입 연산자를 삭제합니다.
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
 * @brief 멤버 함수 포인터를 std::bind로 래핑하여 Event 콜백 함수 객체를 생성합니다.
 * @param[in] pfn 멤버 함수 포인터 (예: &MyClass::OnEvent)
 * @return std::function<void(vega::Event&)> 형태로 사용 가능한 바인딩 함수 객체
 */
#define VG_BIND_CALLBACK_FN(pfn)                        \
    std::bind(&pfn, this, std::placeholders::_1)
