#include "pch.h"
#include "Geometrics.h"

using namespace DX;

bool Geometrics::IntersectInPlaneSphere(PlaneInf plane, Sphere sph)
{
	float proj = Dot(Sub(sph.p, plane.p), plane.n);

	return ((proj + sph.rad) > 0);
}

bool Geometrics::IntersectRaySphere(Ray ray, Sphere sph)
{
	DirectX::XMFLOAT3 toRayPt = Sub(ray.o, sph.p);
	DirectX::XMFLOAT3 tempRight = Normalize(Cross(ray.d, toRayPt));
	DirectX::XMFLOAT3 dir = Cross(tempRight, ray.d);

	return (Dot(toRayPt, dir) < sph.rad);
}

bool Geometrics::IntersectRayPlaneInf(const Ray ray, const PlaneInf plane, DirectX::XMFLOAT3* itsPt)
{
	float dirDot = Dot(ray.d, plane.n);
	if (dirDot == 0)
		return false;

	float t = Dot(plane.n, Sub(plane.p, ray.o)) / dirDot;
	*itsPt = Add({ ray.o , Mul(ray.d , t) });

	return true;
}

bool Geometrics::IntersectRayPlane(Ray ray, Plane plane, DirectX::XMFLOAT3* itsPt)
{
	float dirDot = Dot(ray.d, plane.normal);
	if (dirDot == 0)
		return false;

	float t = Dot(plane.normal, Sub(plane.c, ray.o)) / dirDot;
	DirectX::XMFLOAT3 pt = Add({ ray.o , Mul(ray.d, t) });
	float xDist = abs(Dot(plane.right, Sub(pt, plane.c)));
	float yDist = abs(Dot(plane.up, Sub(pt, plane.c)));
	if (itsPt)
		*itsPt = pt;

	return (
		(Dot(ray.d, Sub(pt, ray.o)) > 0) && // check if ray is ahead of plane
		(xDist < plane.rad.x) &&  // check if hitPt is in x range
		(yDist < plane.rad.y) // check if hitPt is in y range
		);
}

bool Geometrics::Intersect2DRayLine(Ray2D ray, DirectX::XMFLOAT2 linePt1, DirectX::XMFLOAT2 linePt2)
{
	DirectX::XMFLOAT2 o = ray.p;
	DirectX::XMFLOAT2 d = ray.d;
	DirectX::XMFLOAT2 a = linePt1;
	DirectX::XMFLOAT2 b = linePt2;

	if (Equal(a, b) || Equal(d, { 0,0 }))
		return false;
	/*
	±âº»
	o+t1*d = a+t2*(b-a)

	t1
	oX(b-a) + t1 * dX(b-a) = aX(b-a)
	t1 = |(a-o)X(b-a)| / |dX(b-a)|

	t2
	same way

	*/
	float t1 = ((a.x - o.x) * (b.y - a.y) - (a.y - o.y) * (b.x - a.x)) / (d.x * (b.y - a.y) - d.y * (b.x - a.x));
	float t2 = ((o.x - a.x) * d.y - (o.y - a.y) * d.x) / ((b.x - a.x) * d.y - (b.y - a.y) * d.x);

	return (t1 > 0 && 0 < t2 && t2 <= 1);
}
