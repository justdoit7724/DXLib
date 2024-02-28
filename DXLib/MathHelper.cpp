#include "pch.h"
#include "MathHelper.h"

namespace DX {

	XMFLOAT2 Add(std::vector<XMFLOAT2> a)
	{
		XMFLOAT2 out = { 0,0 };
		for (int i = 0; i < a.size(); ++i)
		{
			out.x += a[i].x;
			out.y += a[i].y;
		}

		return out;
	}
	XMFLOAT2 Sub(XMFLOAT2 a, XMFLOAT2 b)
	{
		XMFLOAT2 out;
		out.x = a.x - b.x;
		out.y = a.y - b.y;

		return out;
	}
	XMFLOAT2 Add(XMFLOAT2 a, float v)
	{

		XMFLOAT2 out;
		out.x = a.x + v;
		out.y = a.y + v;

		return out;
	}
	XMFLOAT2 Sub(XMFLOAT2 a, float v)
	{
		XMFLOAT2 out;
		out.x = a.x - v;
		out.y = a.y - v;

		return out;
	}
	XMFLOAT2 Div(XMFLOAT2 a, float v)
	{
		XMFLOAT2 out;
		out.x = a.x / v;
		out.y = a.y / v;

		return out;
	}
	XMFLOAT2 Mul(XMFLOAT2 a, float v)
	{
		XMFLOAT2 out;
		out.x = a.x * v;
		out.y = a.y * v;

		return out;
	}
	XMFLOAT2 Neg(XMFLOAT2 a)
	{
		return { -a.x, -a.y };
	}
	bool Equal(XMFLOAT2 a, XMFLOAT2 b)
	{
		float eps = 1.0e-8;

		return (abs(a.x - b.x) < eps && abs(a.y - b.y) < eps);
	}
	XMFLOAT3 Add(std::vector<XMFLOAT3> a)
	{
		XMFLOAT3 out = { 0,0 ,0};
		for (int i = 0; i < a.size(); ++i)
		{
			out.x += a[i].x;
			out.y += a[i].y;
			out.z += a[i].z;
		}

		return out;
	}
	XMFLOAT3 Sub(XMFLOAT3 a, XMFLOAT3 b)
	{
		XMFLOAT3 out;
		out.x = a.x - b.x;
		out.y = a.y - b.y;
		out.z = a.z - b.z;

		return out;
	}
	XMFLOAT3 Add(XMFLOAT3 a, float v)
	{
		XMFLOAT3 out;
		out.x = a.x + v;
		out.y = a.y + v;
		out.z = a.z + v;
		return out;
	}
	XMFLOAT3 Sub(XMFLOAT3 a, float v)
	{
		XMFLOAT3 out;
		out.x = a.x - v;
		out.y = a.y - v;
		out.z = a.z - v;
		return out;
	}
	XMFLOAT3 Div(XMFLOAT3 a, float v)
	{
		XMFLOAT3 out;
		out.x = a.x / v;
		out.y = a.y / v;
		out.z = a.z / v;
		return out;
	}
	XMFLOAT3 Mul(XMFLOAT3 a, float v)
	{
		XMFLOAT3 out;
		out.x = a.x * v;
		out.y = a.y * v;
		out.z = a.z * v;
		return out;
	}
	bool Equal(XMFLOAT3 a, XMFLOAT3 b)
	{
		float eps = 1.0e-8;

		return (abs(a.x - b.x) < eps && abs(a.y - b.y) < eps && abs(a.z - b.z) < eps);
	}
	XMFLOAT3 Neg(XMFLOAT3 a)
	{
		return { -a.x, -a.y , -a.z};
	}
	XMFLOAT4 Div(XMFLOAT4 a, float v)
	{
		return {a.x/v, a.y/v,a.z/v, a.w/v};
	}
	float Clamp(float a, float b, float v)
	{
		return fmaxf(a, fminf(v, b));
	}

	 float Lerp(float v1, float v2, float t)
	{
		return v1 + (v2 - v1) * Clamp(0, 1, t);
	}

	 float Rand01()
	{
		return (rand() / (float)RAND_MAX);
	}

	 float Length(XMFLOAT2 v)
	{
		return sqrtf(v.x * v.x + v.y * v.y);
	}

	 XMFLOAT2 Cross(XMFLOAT2 a, XMFLOAT2 b)
	{
		XMVECTOR v = XMVector2Cross(XMLoadFloat2(&a), XMLoadFloat2(&b));
		XMFLOAT2 f2;
		XMStoreFloat2(&f2, v);
		return f2;
	}

	 float Dot(XMFLOAT2 a, XMFLOAT2 b)
	{
		XMVECTOR v = XMVector2Dot(XMLoadFloat2(&a), XMLoadFloat2(&b));
		XMFLOAT2 f2;
		XMStoreFloat2(&f2, v);
		return f2.x;
	}

	 XMFLOAT3 Multiply(XMFLOAT3 v, const XMMATRIX& m)
	{
		XMVECTOR mv = XMVector3Transform(XMLoadFloat3(&v), m);
		XMFLOAT3 f3;
		XMStoreFloat3(&f3, mv);
		return f3;
	}

	 XMFLOAT3 MultiplyDir(XMFLOAT3 v, const XMMATRIX& m)
	{
		XMVECTOR mv = XMVector3TransformNormal(XMLoadFloat3(&v), m);
		XMFLOAT3 f3;
		XMStoreFloat3(&f3, mv);
		return f3;
	}

	 float Length(XMFLOAT3 v)
	{
		return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	 XMFLOAT3 Cross(XMFLOAT3 a, XMFLOAT3 b)
	{
		XMVECTOR v = XMVector3Cross(XMLoadFloat3(&a), XMLoadFloat3(&b));
		XMFLOAT3 f3;
		XMStoreFloat3(&f3, v);
		return f3;
	}

	 XMFLOAT3 Lerp(XMFLOAT3 v1, XMFLOAT3 v2, float t)
	{
		 return Add({ v1 , Mul((Sub(v2, v1)) , Clamp(0, 1, t)) });
	}

	 float Dot(XMFLOAT3 a, XMFLOAT3 b)
	{
		XMVECTOR v = XMVector3Dot(XMLoadFloat3(&a), XMLoadFloat3(&b));
		XMFLOAT3 f3;
		XMStoreFloat3(&f3, v);
		return f3.x;
	}

	 XMFLOAT3 Normalize(XMFLOAT3 v)
	{
		XMVECTOR nv = XMVector3Normalize(XMLoadFloat3(&v));
		XMFLOAT3 f3;
		XMStoreFloat3(&f3, nv);
		return f3;
	}

	 XMFLOAT3 Abs(XMFLOAT3 v)
	{
		XMFLOAT3 sum;
		sum.x = abs(v.x);
		sum.y = abs(v.y);
		sum.z = abs(v.z);
		return sum;
	}

	float Max(XMFLOAT3 v)
	{
		return XMMax(v.x, XMMax(v.y, v.z));
	}

	float Rad(XMFLOAT3 d1, XMFLOAT3 d2)
	{
		return acosf(Dot(d1, d2));
	}

	XMFLOAT3 RotateFromDir(XMFLOAT3 p, XMFLOAT3 dir, float rad)
	{
		XMFLOAT3 c = Mul(dir , Dot(dir, p));
		XMFLOAT3 right = Sub(p , c);
		XMFLOAT3 up = Cross(dir, right);

		return Add({ c , Mul(right , cosf(rad)) , Mul(up , sinf(rad)) });
	}

	XMFLOAT4 Multiply(XMFLOAT4 v, const XMMATRIX& m)
	{
		XMVECTOR mv = XMVector4Transform(XMLoadFloat4(&v), m);
		XMFLOAT4 f4;
		XMStoreFloat4(&f4, mv);
		return f4;
	}
	XMFLOAT3 GetColorScale(float t)
	{
		float r = 0;
		float g = 0;
		float b = 0;

		if (t < 0.5)
		{
			b = Lerp(1, 0, t*2);
			g = 1 - b;
		}
		else
		{
			r = Lerp(0, 1, (t-0.5)*2);
			g = 1 - r;
		}

		return { r, g, b };
	}
	XMFLOAT3 GetGrayScale(float t)
	{
		return { t, t, t };
	}
}