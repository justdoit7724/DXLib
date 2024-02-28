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

#define FORWARD XMFLOAT3(0,0,1)
#define BACKWARD XMFLOAT3(0,0,-1)
#define RIGHT XMFLOAT3(1,0,0)
#define LEFT XMFLOAT3(-1,0,0)
#define UP XMFLOAT3(0,1,0)
#define DOWN XMFLOAT3(0,-1,0)


#define DARK_GRAY XMFLOAT4(0.2,0.2,0.2,1)

using namespace DirectX;


namespace DX {






#define MB(s) \
MessageBox(0,s,0,0);\
exit(-1);

#define r_assert(r)	\
assert(SUCCEEDED(r))

	inline std::string ToString(float f, int fracCount=2)
	{

		std::string ret = std::to_string(f);
		auto dot = ret.find('.');
		if (fracCount == 0)
		{
			return ret.substr(0, dot);
		}
		if (dot != std::string::npos)
			return ret.substr(0, dot + 1 + fracCount);

		return ret;
	}

	inline std::string ToString(DirectX::XMFLOAT3 v)
	{
		std::string ret = "";

		std::string x= std::to_string(v.x);
		std::string y= std::to_string(v.y);
		std::string z = std::to_string(v.z);
		auto dot = x.find('.');
		if (dot == std::string::npos)
		{
			ret += x;
		}
		else
			ret += x.substr(0, dot + 1 + 2);
		ret += ", ";
		dot = y.find('.');
		if (dot == std::string::npos)
		{
			ret += y;
		}
		else
			ret += y.substr(0, dot + 1 + 2);
		ret += ", ";
		dot = z.find('.');
		if (dot == std::string::npos)
		{
			ret += z;
		}
		else
			ret += z.substr(0, dot + 1 + 2);

		return ret;
	}

	inline std::string ToString(DirectX::XMFLOAT4 v)
	{
		std::string ret = "";

		std::string x = std::to_string(v.x);
		std::string y = std::to_string(v.y);
		std::string z = std::to_string(v.z);
		std::string w = std::to_string(v.w);
		auto dot = x.find('.');
		if (dot == std::string::npos)
		{
			ret += x;
		}
		else
			ret += x.substr(0, dot + 1 + 2);
		ret += ", ";
		dot = y.find('.');
		if (dot == std::string::npos)
		{
			ret += y;
		}
		else
			ret += y.substr(0, dot + 1 + 2);
		ret += ", ";
		dot = z.find('.');
		if (dot == std::string::npos)
		{
			ret += z;
		}
		else
			ret += w.substr(0, dot + 1 + 2);
		ret += ", ";
		dot = w.find('.');
		if (dot == std::string::npos)
		{
			ret += w;
		}
		else
			ret += w.substr(0, dot + 1 + 2);


		return ret;
	}

}


#endif //PCH_H
