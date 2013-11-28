#pragma once
#include <string>

std::string LoadStringA(_In_opt_ HINSTANCE InstanceHandle, _In_ UINT uID);
std::wstring LoadStringW(_In_opt_ HINSTANCE InstanceHandle, _In_ UINT uID);
#ifndef LoadString
#ifdef UNICODE
#define LoadString  LoadStringW
#else
#define LoadString  LoadStringA
#endif // !UNICODE
#endif

// Windows API QueryPerformanceFrequency()�� ����ȭ�� ����
LONGLONG QueryPerformanceFrequency();
// Windows API QueryPerformanceCounter()�� ����ȭ�� ����
LONGLONG QueryPerformanceCounter();
