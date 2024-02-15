#pragma once

#include <DirectXMath.h>
#include <vector>

namespace DX {

	/*
	DirectX::XMFLOAT2 operator+(DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b)
	{
		return DirectX::XMFLOAT2(a.x + b.x, a.y + b.y);
	}

	DirectX::XMFLOAT2 operator-(DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b)
	{
		return DirectX::XMFLOAT2(a.x - b.x, a.y - b.y);
	}

	DirectX::XMFLOAT2 operator+(DirectX::XMFLOAT2 v, float f)
	{
		return DirectX::XMFLOAT2(v.x + f, v.y + f);
	}

	DirectX::XMFLOAT2 operator-(DirectX::XMFLOAT2 v, float f)
	{
		return DirectX::XMFLOAT2(v.x - f, v.y - f);
	}

	DirectX::XMFLOAT2 operator*(DirectX::XMFLOAT2 v, float f)
	{
		return DirectX::XMFLOAT2(v.x * f, v.y * f);
	}

	DirectX::XMFLOAT2 operator/(DirectX::XMFLOAT2 v, float f)
	{
		return DirectX::XMFLOAT2(v.x / f, v.y / f);
	}

	DirectX::XMFLOAT3 operator+(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b)
	{
		DirectX::XMFLOAT3 sum;
		sum.x = a.x + b.x;
		sum.y = a.y + b.y;
		sum.z = a.z + b.z;
		return sum;
	}

	void operator+=(DirectX::XMFLOAT3& a, DirectX::XMFLOAT3 b)
	{
		a.x += b.x;
		a.y += b.y;
		a.z += b.z;
	}

	DirectX::XMFLOAT3 operator-(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b)
	{
		DirectX::XMFLOAT3 sum;
		sum.x = a.x - b.x;
		sum.y = a.y - b.y;
		sum.z = a.z - b.z;
		return sum;
	}

	DirectX::XMFLOAT3 operator-(DirectX::XMFLOAT3 v)
	{
		DirectX::XMFLOAT3 sum;
		sum.x = -v.x;
		sum.y = -v.y;
		sum.z = -v.z;
		return sum;
	}

	DirectX::XMFLOAT3 operator+(DirectX::XMFLOAT3 v, float f)
	{
		DirectX::XMFLOAT3 sum;
		sum.x = v.x + f;
		sum.y = v.y + f;
		sum.z = v.z + f;
		return sum;
	}

	DirectX::XMFLOAT3 operator-(DirectX::XMFLOAT3 v, float f)
	{
		DirectX::XMFLOAT3 sum;
		sum.x = v.x - f;
		sum.y = v.y - f;
		sum.z = v.z - f;
		return sum;
	}

	DirectX::XMFLOAT3 operator*(DirectX::XMFLOAT3 v, float f)
	{
		DirectX::XMFLOAT3 sum;
		sum.x = v.x * f;
		sum.y = v.y * f;
		sum.z = v.z * f;
		return sum;
	}

	DirectX::XMFLOAT3 operator*(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b)
	{
		DirectX::XMFLOAT3 sum;
		sum.x = a.x * b.x;
		sum.y = a.y * b.y;
		sum.z = a.z * b.z;
		return sum;
	}

	DirectX::XMFLOAT3 operator/(DirectX::XMFLOAT3 v, float f)
	{
		DirectX::XMFLOAT3 sum;
		sum.x = v.x / f;
		sum.y = v.y / f;
		sum.z = v.z / f;
		return sum;
	}

	void operator/=(XMFLOAT4& v, float f)
	{
		v.x /= f;
		v.y /= f;
		v.z /= f;
		v.w /= f;
	}

	bool operator==(DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b)
	{
		return (a.x == b.x && a.y == b.y);
	}

	bool operator!=(DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b)
	{
		return (a.x != b.x || a.y != b.y);
	}

	bool operator==(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b)
	{
		return (a.x == b.x && a.y == b.y && a.z == b.z);
	}

	bool operator!=(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b)
	{
		return (a.x != b.x || a.y != b.y || a.z != b.z);
	}

	bool operator==(XMFLOAT4 a, XMFLOAT4 b)
	{
		return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
	}

	bool operator!=(XMFLOAT4 a, XMFLOAT4 b)
	{
		return (a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w);
	}

	XMFLOAT4 operator*(XMFLOAT4 v, float f)
	{
		return XMFLOAT4(v.x * f, v.y * f, v.z * f, v.w * f);
	}
	*/

	DirectX::XMFLOAT2 DXLIB_DLL Add(std::vector<DirectX::XMFLOAT2> a);
	DirectX::XMFLOAT2 DXLIB_DLL Sub(DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b);
	DirectX::XMFLOAT2 DXLIB_DLL Add(DirectX::XMFLOAT2 a, float v);
	DirectX::XMFLOAT2 DXLIB_DLL Sub(DirectX::XMFLOAT2 a, float v);
	DirectX::XMFLOAT2 DXLIB_DLL Div(DirectX::XMFLOAT2 a, float v);
	DirectX::XMFLOAT2 DXLIB_DLL Mul(DirectX::XMFLOAT2 a, float v);
	DirectX::XMFLOAT2 DXLIB_DLL Neg(DirectX::XMFLOAT2 a);
	bool DXLIB_DLL Equal(DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b);
	DirectX::XMFLOAT3 DXLIB_DLL Add(std::vector<DirectX::XMFLOAT3> a);
	DirectX::XMFLOAT3 DXLIB_DLL Sub(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b);
	DirectX::XMFLOAT3 DXLIB_DLL Add(DirectX::XMFLOAT3 a, float v);
	DirectX::XMFLOAT3 DXLIB_DLL Sub(DirectX::XMFLOAT3 a, float v);
	DirectX::XMFLOAT3 DXLIB_DLL Div(DirectX::XMFLOAT3 a, float v);
	DirectX::XMFLOAT3 DXLIB_DLL Mul(DirectX::XMFLOAT3 a, float v);
	bool DXLIB_DLL Equal(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b);
	DirectX::XMFLOAT3 DXLIB_DLL Neg(DirectX::XMFLOAT3 a);
	
	

	float DXLIB_DLL Clamp(float a, float b, float v);
	float DXLIB_DLL Lerp(float v1, float v2, float t);
	float DXLIB_DLL Rand01();
	float DXLIB_DLL Length(DirectX::XMFLOAT2 v);
	DirectX::XMFLOAT2 DXLIB_DLL Cross(DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b);
	float DXLIB_DLL Dot(DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b);
	DirectX::XMFLOAT3 DXLIB_DLL Multiply(DirectX::XMFLOAT3 v, const DirectX::XMMATRIX& m);
	DirectX::XMFLOAT3 DXLIB_DLL MultiplyDir(DirectX::XMFLOAT3 v, const DirectX::XMMATRIX& m);
	float DXLIB_DLL Length(DirectX::XMFLOAT3 v);
	DirectX::XMFLOAT3 DXLIB_DLL Cross(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b);
	DirectX::XMFLOAT3 DXLIB_DLL Lerp(DirectX::XMFLOAT3 v1, DirectX::XMFLOAT3 v2, float t);
	float DXLIB_DLL Dot(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b);
	DirectX::XMFLOAT3 DXLIB_DLL Normalize(DirectX::XMFLOAT3 v);
	DirectX::XMFLOAT3 DXLIB_DLL Abs(DirectX::XMFLOAT3 v);
	float DXLIB_DLL Max(DirectX::XMFLOAT3 v);
	// radian between dir1, dir2
	float DXLIB_DLL Rad(DirectX::XMFLOAT3 d1, DirectX::XMFLOAT3 d2);
	DirectX::XMFLOAT3 DXLIB_DLL RotateFromDir(DirectX::XMFLOAT3 p, DirectX::XMFLOAT3 dir, float rad);

	DirectX::XMFLOAT4 DXLIB_DLL Multiply(DirectX::XMFLOAT4 v, const DirectX::XMMATRIX& m);

	DirectX::XMFLOAT3 DXLIB_DLL GetColorScale(float t);
	DirectX::XMFLOAT3 DXLIB_DLL GetGrayScale(float t);

	const float PI = 3.141592;
}

