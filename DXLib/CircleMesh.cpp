#include "pch.h"
#include "CircleMesh.h"

using namespace DX;

CircleMesh::CircleMesh(ID3D11Device* device, int sCount)
{
	assert(sCount >= 3);


	float dTheta = XM_2PI / sCount;
	float rad = 0.5;

	for (int i = 0; i < sCount + 1; ++i)
	{
		Vertex vert;

		float x = rad * cosf(i * dTheta);
		float z = rad * sinf(i * dTheta);
		float u = x / 1.5f;
		float v = z / 1.5f;

		vert.pos = XMFLOAT3(x, 0, z);
		vert.tex = XMFLOAT2(u, v);
		vert.normal = UP;

		m_vertice.push_back(vert);
	}

	Vertex vert;
	vert.pos = XMFLOAT3(0, 0, 0);
	vert.tex = XMFLOAT2(0.5f, 0.5f);
	vert.normal = UP;
	m_vertice.push_back(vert);

	std::vector<int> indice;
	int centerIdx = Count()-1;
	for (int i = 0; i < sCount; ++i)
	{
		indice.push_back(centerIdx);
		indice.push_back(i + 1);
		indice.push_back(i);
	}


	SetIndice(indice.data(), indice.size());
}
