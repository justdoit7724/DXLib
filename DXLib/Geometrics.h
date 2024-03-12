#pragma once

#ifndef _GEOMETRICS
#define _GEOMETRICS

#include "MathHelper.h"

namespace DX {

	namespace Geometrics {

		struct Sphere {
		public:
			DirectX::XMFLOAT3 p;
			float rad;

			Sphere() :p(DirectX::XMFLOAT3(0, 0, 0)), rad(1) {}
			Sphere(DirectX::XMFLOAT3 p, float rad) :p(p), rad(rad) {}
		};
		struct PlaneInf {
		public:
			DirectX::XMFLOAT3 p;
			DirectX::XMFLOAT3 n;
			PlaneInf() :p(DirectX::XMFLOAT3(0, 0, 0)), n(DirectX::XMFLOAT3(0, 0, 0)) {}
			PlaneInf(DirectX::XMFLOAT3 p, DirectX::XMFLOAT3 n) :p(p), n(n) {}
		};
		struct Plane {
		public:
			DirectX::XMFLOAT3 c;
			DirectX::XMFLOAT3 normal;
			DirectX::XMFLOAT3 up;
			DirectX::XMFLOAT3 right;
			DirectX::XMFLOAT2 rad;
			Plane() :c(DirectX::XMFLOAT3(0, 0, 0)), normal(DirectX::XMFLOAT3(0, 0, 0)), up(DirectX::XMFLOAT3(0, 0, 0)), right(DirectX::XMFLOAT3(0, 0, 0)), rad(DirectX::XMFLOAT2(0, 0)) {}
			Plane(DirectX::XMFLOAT3 c, DirectX::XMFLOAT3 normal, DirectX::XMFLOAT3 up, DirectX::XMFLOAT2 rad) :c(c), normal(normal), up(up), right(Cross(up, normal)), rad(rad) {}
		};
		struct Bound {
		public:
			DirectX::XMFLOAT3 center;
			DirectX::XMFLOAT3 rad;
			Bound() : center(DirectX::XMFLOAT3(0, 0, 0)), rad(DirectX::XMFLOAT3(0, 0, 0)) {}
			Bound(DirectX::XMFLOAT3 c, DirectX::XMFLOAT3 rad) :center(c), rad(rad) {}
		};
		struct Ray {

		public:
			DirectX::XMFLOAT3 o;
			DirectX::XMFLOAT3 d;

			Ray() :o(DirectX::XMFLOAT3(0, 0, 0)), d(DirectX::XMFLOAT3(0, 0, 0)) {}
			Ray(const DirectX::XMFLOAT3& o, const DirectX::XMFLOAT3& d) : o(o), d(d) {}

			DirectX::XMFLOAT3 operator() (float t) const;
		};
		struct Ray2D {
		public:
			DirectX::XMFLOAT2 p;
			DirectX::XMFLOAT2 d;

			Ray2D() {
				p = DirectX::XMFLOAT2(0, 0);
				d = DirectX::XMFLOAT2(0, 1);
			}
			Ray2D(DirectX::XMFLOAT2 pt, DirectX::XMFLOAT2 dir)
			{
				p = pt;
				d = dir;
			}
		};

		bool DXLIB_DLL IntersectInPlaneSphere(PlaneInf plane, Sphere sph);
		// infinite ray
		bool DXLIB_DLL IntersectRaySphere(Ray ray, Sphere sph);
		bool DXLIB_DLL IntersectRayPlaneInf(const Ray ray, const PlaneInf plane, DirectX::XMFLOAT3* itsPt);
		// considered infinite ray & both plane side
		bool DXLIB_DLL IntersectRayPlane(Ray ray, Plane plane, DirectX::XMFLOAT3* itsPt);
		bool DXLIB_DLL Intersect2DRayLine(Ray2D ray, DirectX::XMFLOAT2 linePt1, DirectX::XMFLOAT2 linePt2);
	}
}

#endif

