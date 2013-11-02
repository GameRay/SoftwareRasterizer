#pragma once


// windows ���
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

// C++ ���
#include <string>
#include <memory>
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

#include <functional>
using std::function;

// ����� ���
#include "ErrorReporter.h"
#include "Uncopyable.h"
#include "Utility.h"
