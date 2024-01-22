
#include "pch.h"
#include "CylinderMesh.h"
#include "ShaderFormat.h"
#include "Math.h"

using namespace DX;

CylinderMesh::CylinderMesh(ID3D11Device* device, int sliceCount, const VertexLayout* layout)
{
	assert(sliceCount >= 3);

#pragma region side

	float dTheta = XM_2PI / sliceCount;
	float hHeight = 0.5;
	float rad = 0.5;

	Vertice vertice(*layout);

	const bool isPos3 = layout->Resolve<VE_Position3D>();
	const bool isTex = layout->Resolve<VE_Texture2D>();
	const bool isNorm = layout->Resolve<VE_Normal>();
	
	int vertCount = 0;
	for (int i = 0; i < 2; ++i) {
		float y = -hHeight + i;

		for (int j = 0; j <= sliceCount; ++j) {

			vertice.EmplaceBack();

			float c = cosf(j * dTheta);
			float s = sinf(j * dTheta);

			XMFLOAT3 tangent = XMFLOAT3(-s, 0, c);
			XMFLOAT3 bitangent = -UP;

			if(isPos3)
				vertice[vertCount].Attr<VE_Position3D>() = XMFLOAT3(rad * c, y, rad * s);
			if(isTex)
				vertice[vertCount].Attr<VE_Texture2D>() = XMFLOAT2(float(j) / sliceCount, 1.0f - i);
			if(isNorm)
				vertice[vertCount].Attr<VE_Normal>() = Cross(tangent, bitangent);
			
			vertCount++;
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
	int baseIdx = vertice.Count();
	for (int i = 0; i < sliceCount + 1; ++i)
	{
		vertice.EmplaceBack();

		float x = rad * cosf(i * dTheta);
		float z = rad * sinf(i * dTheta);
		float u = x / 1.5f;
		float v = z / 1.5f;

		if (isPos3)
			vertice[vertCount].Attr<VE_Position3D>() = XMFLOAT3(x, hHeight, z);
		if (isTex)
			vertice[vertCount].Attr<VE_Texture2D>() = XMFLOAT2(u, v);
		if (isNorm)
			vertice[vertCount].Attr<VE_Normal>() = UP;

		vertCount++;
	}

	vertice.EmplaceBack();
	if (isPos3)
		vertice[vertCount].Attr<VE_Position3D>() = XMFLOAT3(0, hHeight, 0);
	if (isTex)
		vertice[vertCount].Attr<VE_Texture2D>() = XMFLOAT2(0.5f, 0.5f);
	if (isNorm)
		vertice[vertCount].Attr<VE_Normal>() = UP;
	vertCount++;
	
	int centerIdx = vertice.Count();
	for (int i = 0; i < sliceCount; ++i)
	{
		indice.push_back(centerIdx-1);
		indice.push_back(baseIdx + i + 1);
		indice.push_back(baseIdx + i);
	}

	//bottom
	baseIdx = vertice.Count();
	for (int i = 0; i < sliceCount + 1; ++i)
	{
		vertice.EmplaceBack();

		float x = rad * cosf(i * dTheta);
		float z = rad * sinf(i * dTheta);
		float u = x / 1.5f;
		float v = z / 1.5f;


		if (isPos3)
			vertice[vertCount].Attr<VE_Position3D>() = XMFLOAT3(x, -hHeight, z);
		if (isTex)
			vertice[vertCount].Attr<VE_Texture2D>() = XMFLOAT2(u, v);
		if (isNorm)
			vertice[vertCount].Attr<VE_Normal>() = -UP;
		vertCount++;

	}

	vertice.EmplaceBack();
	if (isPos3)
		vertice[vertCount].Attr<VE_Position3D>() = XMFLOAT3(0, -hHeight, 0);
	if (isTex)
		vertice[vertCount].Attr<VE_Texture2D>() = XMFLOAT2(0.5f, 0.5f);
	if (isNorm)
		vertice[vertCount].Attr<VE_Normal>() = -UP;
	vertCount++;
	
	centerIdx = vertice.Count();
	for (int i = 0; i < sliceCount; ++i)
	{
		indice.push_back(centerIdx-1);
		indice.push_back(baseIdx + i);
		indice.push_back(baseIdx + i + 1);
	}
#pragma endregion


	SetVertice(&vertice, indice.data(), indice.size());
	Update(device);
}
