
#include "pch.h"

#include "Mesh.h"
#include "ShaderFormat.h"
#include "LineMesh.h"

using namespace DX;

LineMesh::LineMesh()
{
	m_primitiveType = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
}

void LineMesh::Add(XMFLOAT3 a, XMFLOAT3 b)
{
	LineInfo newLine;
	newLine.a = a;
	newLine.b = b;

	lines.push_back(newLine);
}

void LineMesh::Generate(ID3D11Device* device, VertexLayout layout)
{
	isGenerated = true;

	std::vector<int> indice;

	for (int i = 0; i < lines.size(); ++i)
	{
		EmplaceBack(2);

		GetVertex(i * 2).Attr<VE_Position3D>() = lines[i].a;
		GetVertex(i * 2+1).Attr<VE_Position3D>() = lines[i].b;

		indice.push_back(i * 2);
		indice.push_back(i * 2+1);
	}


	SetIndice(indice.data(), indice.size());
	Update(device);
}

void LineMesh::Clear()
{
	lines.clear();
}

void LineMesh::Apply(ID3D11DeviceContext* dContext) const
{
	Mesh::Apply(dContext);
}
