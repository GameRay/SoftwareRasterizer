#pragma once


// windows ���
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

// DirectXMath.h
#include <DirectXMath.h>
#include <DirectXCollision.h>

// C++ ���
#include <queue>
#include <array>
#include <memory>

// Intel TBB
#include <tbb/parallel_for.h>

// Easy D3D
#pragma comment ( lib, "Utility.lib" )
#include <EasyD3D/Utility.h>
#pragma comment ( lib, "Core.lib" )
#include <EasyD3D/EasyD3D.h>