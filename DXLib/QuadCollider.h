#pragma once
#include "Collider.h"
#include "Network.h"

namespace DX {
	class QuadCollider :public Collider
	{
	public:
		QuadCollider();
		QuadCollider(DirectX::XMFLOAT3 pos);

		void Visualize() override;
		bool IsHit(Geometrics::Ray ray, DirectX::XMFLOAT3* hitPt) override;
		void SetScale(DirectX::XMFLOAT3 s) override;
	private:

		DirectX::XMFLOAT2 extent;

	};
}
