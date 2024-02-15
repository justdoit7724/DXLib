
#include "pch.h"
#include "CubeCollider.h"

using namespace DX;

CubeCollider::CubeCollider()
	:Collider(XMFLOAT3(0,0,0)), extent(XMFLOAT3(0.5f,0.5f,0.5f))
{
}

CubeCollider::CubeCollider(XMFLOAT3 center, XMFLOAT3 extent)
	:Collider(center), extent(extent)
{
}

bool CubeCollider::IsHit(Geometrics::Ray ray, XMFLOAT3* hitPt)
{
	XMFLOAT3 right = Cross(up, forward);

	if (Dot(ray.d, right) < 0)
	{
		Geometrics::Plane rightP(Add({ center, Mul(right , extent.x) }), right, up, XMFLOAT2(extent.z, extent.y));

		if (Geometrics::IntersectRayPlane(ray, rightP, hitPt))
			return true;
	}
	if (Dot(ray.d, up) < 0)
	{
		Geometrics::Plane upP(Add({center, Mul(up, extent.y)}), up, Neg(forward), XMFLOAT2(extent.x, extent.z));

		if (IntersectRayPlane(ray, upP, hitPt))
			return true;
	}
	if (Dot(ray.d, forward) < 0)
	{
		Geometrics::Plane forwardP(Add({ center, Mul(forward, extent.z) }), forward, up, XMFLOAT2(extent.x, extent.y));

		if (IntersectRayPlane(ray, forwardP, hitPt))
			return true;
	}
	if (Dot(ray.d, Neg(right)) < 0)
	{
		Geometrics::Plane leftP(Sub(center, Mul(right, extent.x)), Neg(right), up, XMFLOAT2(extent.z, extent.y));

		if (IntersectRayPlane(ray, leftP, hitPt))
			return true;
	}
	if (Dot(ray.d, Neg(up)) < 0)
	{
		Geometrics::Plane downP(Sub(center, Mul(up, extent.y)), Neg(up), forward, XMFLOAT2(extent.x, extent.z));

		if (IntersectRayPlane(ray, downP, hitPt))
			return true;
	}
	if (Dot(ray.d, Neg(forward)) < 0)
	{
		Geometrics::Plane backP(Sub(center, Mul(forward, extent.z)), Neg(forward), up, XMFLOAT2(extent.x, extent.y));

		if (IntersectRayPlane(ray, backP, hitPt))
			return true;
	}

	return false;
}

void CubeCollider::SetScale(XMFLOAT3 s)
{
	extent = Mul(s, 0.5);
}

void CubeCollider::Visualize()
{
	//Debugging::Instance()->MarkCube(center, forward, up, extent);
}
