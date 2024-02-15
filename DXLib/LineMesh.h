#pragma once

#include "Mesh.h"

namespace DX {

	class VertexLayout;

	class DXLIB_DLL LineMesh : public Mesh
	{
	public:
		LineMesh();

		void Add(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b);
		void Generate(ID3D11Device* device, VertexLayout layout);
		void Clear();
		void Apply(ID3D11DeviceContext* dContext) const override;

	private:

		bool isGenerated = false;

		struct LineInfo
		{
			DirectX::XMFLOAT3 a, b;
		};

		std::vector<LineInfo> lines;
	};
}

