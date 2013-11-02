#pragma once


// windows ���
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

// C++ ���
#include <string>
#include <memory>
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

// ����� ���
#include <Uncopyable.h>
#include <ErrorReporter.h>
