
#include "pch.h"
#include "CylinderMesh.h"
#include "ShaderFormat.h"
#include "MathHelper.h"

using namespace DX;

CylinderMesh::CylinderMesh(ID3D11Device* device, int sliceCount)
{
	assert(sliceCount >= 3);

#pragma region side

	float dTheta = XM_2PI / sliceCount;
	float hHeight = 0.5;
	float rad = 0.5;

	for (int i = 0; i < 2; ++i) {
		float y = -hHeight + i;

		for (int j = 0; j <= sliceCount; ++j) {

			Vertex vert;

			float c = cosf(j * dTheta);
			float s = sinf(j * dTheta);

			XMFLOAT3 tangent = XMFLOAT3(-s, 0, c);
			XMFLOAT3 bitangent = DOWN;

			vert.pos = XMFLOAT3(rad * c, y, rad * s);
			vert.tex = XMFLOAT2(float(j) / sliceCount, 1.0f - i);
			vert.normal = Cross(tangent, bitangent);

			m_vertice.push_back(vert);
		}
	}

	std::vector<int> indice;
	int ringVertexCount = sliceCount + 1;
	for (int i = 0; i < ringVertexCount; ++i)
	{
		indice.push_back(i);
		indice.push_back(ringVertexCount + i);
		indice.push_back(ringVertexCount + i + 1);
		indice.push_back(i);
		indice.push_back(ringVertexCount + i + 1);
		indice.push_back(i + 1);
	}
#pragma endregion

#pragma region cap
	// top
	int baseIdx = Count();
	for (int i = 0; i < sliceCount + 1; ++i)
	{
		Vertex vert;

		float x = rad * cosf(i * dTheta);
		float z = rad * sinf(i * dTheta);
		float u = x / 1.5f;
		float v = z / 1.5f;

		vert.pos = XMFLOAT3(x, hHeight, z);
		vert.tex = XMFLOAT2(u, v);
		vert.normal = UP;

		m_vertice.push_back(vert);
	}

	Vertex vert;
	vert.pos = XMFLOAT3(0, hHeight, 0);
	vert.tex = XMFLOAT2(0.5f, 0.5f);
	vert.normal = UP;
	m_vertice.push_back(vert);
	
	int centerIdx = Count();
	for (int i = 0; i < sliceCount; ++i)
	{
		indice.push_back(centerIdx-1);
		indice.push_back(baseIdx + i + 1);
		indice.push_back(baseIdx + i);
	}

	//bottom
	baseIdx = Count();
	for (int i = 0; i < sliceCount + 1; ++i)
	{
		Vertex vert;

		float x = rad * cosf(i * dTheta);
		float z = rad * sinf(i * dTheta);
		float u = x / 1.5f;
		float v = z / 1.5f;

		vert.pos = XMFLOAT3(x, -hHeight, z);
		vert.tex = XMFLOAT2(u, v);
		vert.normal = DOWN;
		
		m_vertice.push_back(vert);
	}

	vert.pos = XMFLOAT3(0, -hHeight, 0);
	vert .tex= XMFLOAT2(0.5f, 0.5f);
	vert .normal= DOWN;
	
	centerIdx = Count();
	for (int i = 0; i < sliceCount; ++i)
	{
		indice.push_back(centerIdx-1);
		indice.push_back(baseIdx + i);
		indice.push_back(baseIdx + i + 1);
	}
#pragma endregion


	SetIndice(indice.data(), indice.size());
	Update(device);
}
