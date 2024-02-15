#pragma once

#include "Collider.h"

namespace DX {
	class DXLIB_DLL SphereCollider : public Collider
	{
	public:
		SphereCollider();
		SphereCollider(DirectX::XMFLOAT3 center, float rad);

		virtual bool IsHit(Geometrics::Ray ray, DirectX::XMFLOAT3* hitPt) override;
		void SetScale(DirectX::XMFLOAT3 s) override;

		void Visualize() override;
	protected:
		float rad;
	private:
	};
}
