#pragma once
#include "Network.h"

#include "Geometrics.h"

namespace DX
{
	class DXLIB_DLL Collider : public IDebug
	{
	public:
		Collider(DirectX::XMFLOAT3 center);

		virtual bool IsHit(Geometrics::Ray ray, DirectX::XMFLOAT3* hitPt) = 0;

		void Translate(DirectX::XMFLOAT3 pt) { center = pt; }
		void SetRotate(DirectX::XMFLOAT3 f, DirectX::XMFLOAT3 u);
		virtual void SetScale(DirectX::XMFLOAT3 s) = 0;

	protected:

		DirectX::XMFLOAT3 center;
		DirectX::XMFLOAT3 forward, up;
	};
}


