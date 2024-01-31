// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H


#ifdef DXLIB_EXPORTS
#define DXLIB_DLL __declspec(dllexport)
#else
#define DXLIB_DLL __declspec(dllimport)
#endif

// add headers that you want to pre-compile here
#include "framework.h"

#pragma once



#ifdef _WIN64

#ifdef _DEBUG
#pragma comment(lib, __FILE__"\\..\\DirectXTK\\x64\\Debug\\DirectXTK.lib")
#else
#pragma comment(lib, __FILE__"\\..\\DirectXTK\\x64\\Release\\DirectXTK.lib")
#endif

#else
S
#ifdef _DEBUG
#pragma comment(lib, __FILE__"\\..\\DirectXTK\\Win32\\Debug\\DirectXTK.lib")
#else
#pragma comment(lib, __FILE__"\\..\\DirectXTK\\Win32\\Release\\DirectXTK.lib")
#endif

#endif




#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib,"d3d11.lib")



#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <assert.h>
#include <string>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <limits>
#include <memory>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <fstream>

using namespace DirectX;


namespace DX {

#define MB(s) \
MessageBox(0,s,0,0);\
exit(-1);

#define r_assert(r)	\
assert(SUCCEEDED(r))

	

}


#endif //PCH_H
