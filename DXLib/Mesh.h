#pragma once

#include "Component.h"


namespace DX {
	
	class Object;

	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 tex;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT4 color;

	};


	class DXLIB_DLL Mesh : public Component
	{
	public:
		Mesh();
		Mesh(const Mesh* other);
		~Mesh();

		void GetLBound(OUT DirectX::XMFLOAT3* minPt, OUT DirectX::XMFLOAT3* maxPt);
		D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveType() { return m_primitiveType; }

		void SetIndice(const int* indice, int indexCount);



		void Apply(const Graphic* graphic) override;


		int Count() const;
		void Resize(int count = 1);
		void SetVertex(int i, Vertex v);
		void SetPos(int i, DirectX::XMFLOAT3 pos);
		void SetColor(int i, DirectX::XMFLOAT4 col);
		void SetColor(DirectX::XMFLOAT4 col);
		Vertex GetVertex(int i) const;
		void Clear();

	protected:

		void Update(ID3D11Device* device);
		void SetPrimitiveType(D3D11_PRIMITIVE_TOPOLOGY p) { m_primitiveType = p; }

		DirectX::XMFLOAT3 m_lMinPt, m_lMaxPt;
		ID3D11Buffer* m_vertexBuffer = nullptr;
		ID3D11Buffer* m_indexBuffer = nullptr;
		D3D11_PRIMITIVE_TOPOLOGY m_primitiveType;


		int* m_indice;
		int m_indexCount;

		std::vector<Vertex> m_vertice;

		bool m_updated;


	};
}
