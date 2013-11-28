#pragma once
#include "Type.h"

#pragma region Uncopyable
// Ŭ���� Uncopyable. �� Ŭ������ ����ϴ� ��� Ŭ������ ���翬���� �Ұ���������.
// Usage : class MyClass : Uncopyable { /* declarations */ };
class Uncopyable
{
protected:
    Uncopyable() = default;
    ~Uncopyable() = default;
    Uncopyable(const Uncopyable&) = delete;
    Uncopyable& operator=(const Uncopyable&) = delete;
};
#pragma endregion
#pragma region Stopwatch
enum class StopwatchStatus { Paused, Running };

// �����ġ Ŭ����. �ð� ������ ���δ�.
class Stopwatch
{
    const static llong CountPerSecond;
    llong countStarted;
    llong countPaused;
    llong countLastTick;

public:
    // �� �����ġ ��ü�� �����Ѵ�
    // Status : ���� ������ �����ġ�� �Ͻ������� ��������, �������� �������� �����Ѵ� (�⺻�� : Paused)
    Stopwatch(StopwatchStatus Status = StopwatchStatus::Paused);

    // �����ִ� �����ġ�� �۵���Ų��. �̹� �۵����̾������, �ƹ����ϵ� �Ͼ�� �ʴ´�.
    void Start();
    // �۵����� �����ġ�� ������Ų��. �̹� �����־������, �ƹ����ϵ� �Ͼ�� �ʴ´�.
    void Pause();

    // �����ġ�� ���۵ǰ��� �� ����� �ð��� ��ȯ�Ѵ�.
    // ��ȯ�� : �����ġ�� ���۵ǰ��� ����� �� �ð�. (���� : ��)
    double getTime() const;
    // �����ġ�� ���� �ð��� ���������, �Ͻ������� �������� ���θ� ��ȯ�Ѵ�.
    // ��ȯ�� : ���� �����ġ�� ����
    StopwatchStatus getStatus() const { return countPaused ? StopwatchStatus::Paused : StopwatchStatus::Running; }

    // ���������� Tick() �Լ��� ȣ������ �ð��� �󸶳� �������� ��ȯ�Ѵ�.
    // ��ȯ�� : ���������� Tick() �Լ��� ȣ���ϰ��� ����� �� �ð�. (���� : ��)
    double Tick();
};
#pragma endregion
#pragma region RAII
#include <functional>

class Raii : Uncopyable
{
    std::function<void()> code;
public:
    template <typename Func> Raii(Func&& Code) : code(std::move(Code)) { }
    ~Raii() { code(); }
};

#define RAII_HELPER2(n) __raiiObject##n
#define RAII_HELPER1(n) Raii RAII_HELPER2(n) = [&]()

// Usage
//     RAII { /* Do something release in here */ };
//     RAII
//     {
//         CoUninitialize();
//         CoTaskMemFree(mem);
//     };
//
// RAII�� ����� ������ �������� ����Ǹ�, RAII �ȿ� ����� �ڵ尡 ����ȴ�
#define RAII RAII_HELPER1(__COUNTER__)

#pragma endregion
#pragma region ErrorReporter
enum class ErrorCodeType { HR, Nonzero, False, Custom };
enum class ErrorReportType { Error, Warning };

void Report(ErrorReportType ReportType, int ErrorCode, ErrorCodeType ErrorCodeType,
    const wchar* FileName, size_t LineNumber, const wchar* Function, const wchar* Command, const wchar* Message);



// Macro Bodies
#define _HR(x, report_type, msg) \
do \
{ \
    int __code = (int)(x); \
if (FAILED(__code)) \
    Report(report_type, __code, ErrorCodeType::HR, __FILEW__, __LINE__, __FUNCTIONW__, L#x, msg); \
} \
while (false)

#define _NONZERO(x, report_type, msg) \
do \
{ \
    int __code = (int)(x); \
if (__code) \
    Report(report_type, __code, ErrorCodeType::Nonzero, __FILEW__, __LINE__, __FUNCTIONW__, L#x, msg); \
} \
while (false)

#define _FALSE(x, report_type, msg) \
do \
{ \
    int __code = (int)(x); \
if (!__code) \
    Report(report_type, __code, ErrorCodeType::False, __FILEW__, __LINE__, __FUNCTIONW__, L#x, msg); \
} \
while (false)

#define _CUSTOM(x, report_type, msg) \
    Report(report_type, 0, ErrorCodeType::Custom, __FILEW__, __LINE__, __FUNCTIONW__, L"", msg);


// Interface Macros
#define HR_ERROR_MSG(x, msg) _HR(x, ErrorReportType::Error, msg)
#define NONZERO_ERROR_MSG(x, msg) _NONZERO(x, ErrorReportType::Error, msg)
#define FALSE_ERROR_MSG(x, msg) _FALSE(x, ErrorReportType::Error, msg)
#define ERROR_MSG(msg) _CUSTOM(0, ErrorReportType::Error, msg)

#ifdef _DEBUG
#define HR_WARNING_MSG(x, msg) _HR(x, ErrorReportType::Warning, msg)
#define NONZERO_WARNING_MSG(x, msg) _NONZERO(x, ErrorReportType::Warning, msg)
#define FALSE_WARNING_MSG(x, msg) _FALSE(x, ErrorReportType::Warning, msg)
#define WARNING_MSG(msg) _CUSTOM(0, ErrorReportType::Warning, msg)
#else
#define HR_WARNING_MSG(x, msg) (x)
#define NONZERO_WARNING_MSG(x, msg) (x)
#define FALSE_WARNING_MSG(x, msg) (x)
#define WARNING_MSG(msg)
#endif

#define HR_ERROR(x) HR_ERROR_MSG(x, nullptr)
#define HR_WARNING(x) HR_WARNING_MSG(x, nullptr)
#define NONZERO_ERROR(x) NONZERO_ERROR_MSG(x, nullptr)
#define NONZERO_WARNING(x) NONZERO_WARNING_MSG(x, nullptr)
#define FALSE_ERROR(x) FALSE_ERROR_MSG(x, nullptr)
#define FALSE_WARNING(x) FALSE_WARNING_MSG(x, nullptr)
#pragma endregion
