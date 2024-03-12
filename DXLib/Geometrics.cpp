#include "pch.h"
#include "Geometrics.h"

using namespace DX;


XMFLOAT3 Geometrics::Ray::operator() (float t) const {

	return  o + d * t;
}

bool Geometrics::IntersectInPlaneSphere(PlaneInf plane, Sphere sph)
{
	float proj = Dot(sph.p- plane.p, plane.n);

	return ((proj + sph.rad) > 0);
}

bool Geometrics::IntersectRaySphere(Ray ray, Sphere sph)
{
	DirectX::XMFLOAT3 toRayPt = ray.o- sph.p;
	DirectX::XMFLOAT3 tempRight = Normalize(Cross(ray.d, toRayPt));
	DirectX::XMFLOAT3 dir = Cross(tempRight, ray.d);

	return (Dot(toRayPt, dir) < sph.rad);
}

bool Geometrics::IntersectRayPlaneInf(const Ray ray, const PlaneInf plane, DirectX::XMFLOAT3* itsPt)
{
	float dirDot = Dot(ray.d, plane.n);
	if (dirDot == 0)
		return false;

	float t = Dot(plane.n, plane.p- ray.o) / dirDot;
	*itsPt = ray.o + ray.d * t;

	return true;
}

bool Geometrics::IntersectRayPlane(Ray ray, Plane plane, DirectX::XMFLOAT3* itsPt)
{
	float dirDot = Dot(ray.d, plane.normal);
	if (dirDot == 0)
		return false;

	float t = Dot(plane.normal, plane.c- ray.o) / dirDot;
	DirectX::XMFLOAT3 pt = ray.o + ray.d* t;
	float xDist = abs(Dot(plane.right, pt- plane.c));
	float yDist = abs(Dot(plane.up, pt- plane.c));
	if (itsPt)
		*itsPt = pt;

	return (
		(Dot(ray.d, pt- ray.o) > 0) && // check if ray is ahead of plane
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
