#pragma once

#include "Component.h"
#include "Vertex.h"

namespace DX {
	class Vertice;
	class Object;


	class DXLIB_DLL Mesh : public Component
	{
	public:
		Mesh();
		~Mesh();

		void GetLBound(OUT XMFLOAT3* minPt, OUT XMFLOAT3* maxPt);
		D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveType() { return m_primitiveType; }

		Vertex GetVertex(int index);
		int VertexCount();
		void SetVertex(int index, Vertex vertex);
		void SetVertice(const Vertice* vertice, const int* indice, int indexCount);
		void Update(ID3D11Device* device);


		void Apply(ID3D11DeviceContext* dContext)const override;

	protected:

		void SetPrimitiveType(D3D11_PRIMITIVE_TOPOLOGY p) { m_primitiveType = p; }

		XMFLOAT3 m_lMinPt, m_lMaxPt;
		ID3D11Buffer* m_vertexBuffer = nullptr;
		ID3D11Buffer* m_indexBuffer = nullptr;
		D3D11_PRIMITIVE_TOPOLOGY m_primitiveType;

		Vertice* m_vertice;

		int* m_indice;
		int m_indexCount;

		bool isNeedUpdate;
	};
}
