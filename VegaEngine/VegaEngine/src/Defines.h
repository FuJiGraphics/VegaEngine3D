#pragma once

/*
* @brief ���� ������, ���� ���� �����ڸ� �����մϴ�.
*/
#define VG_DELETE_COPY(ClassName)                       \
    ClassName(const ClassName&) = delete;               \
    ClassName& operator=(const ClassName&) = delete;