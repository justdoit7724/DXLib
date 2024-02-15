#pragma once
#include "Collider.h"

namespace DX
{
	class CubeCollider : public Collider
	{
	public:
		CubeCollider();
		CubeCollider(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 extent);

		bool IsHit(Geometrics::Ray ray, DirectX::XMFLOAT3* hitPt) override;
		void SetScale(DirectX::XMFLOAT3 s) override;
		void Visualize() override;

	private:

		DirectX::XMFLOAT3 extent;
	};
}