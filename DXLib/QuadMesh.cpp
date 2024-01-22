
#include "pch.h"

#include "QuadMesh.h"
#include "ShaderFormat.h"
#include "Math.h"
#include "Vertex.h"

using namespace DX;

QuadMesh::QuadMesh(ID3D11Device* device, const VertexLayout* layout)
	: Mesh()
{

	Vertice OBJ_QUAD(*layout);
	OBJ_QUAD.EmplaceBack();
	OBJ_QUAD.EmplaceBack();
	OBJ_QUAD.EmplaceBack();
	OBJ_QUAD.EmplaceBack();

	OBJ_QUAD[0].Attr<VE_Position3D>() = XMFLOAT3(-0.5, -0.5, 0);
	OBJ_QUAD[1].Attr<VE_Position3D>() = XMFLOAT3(-0.5, 0.5, 0);
	OBJ_QUAD[2].Attr<VE_Position3D>() = XMFLOAT3(0.5, 0.5, 0);
	OBJ_QUAD[3].Attr<VE_Position3D>() = XMFLOAT3(0.5, -0.5, 0);

	if (layout->Resolve<VE_Texture2D>())
	{
		OBJ_QUAD[0].Attr<VE_Texture2D>() = XMFLOAT2(1, 1);
		OBJ_QUAD[1].Attr<VE_Texture2D>() = XMFLOAT2(1, 0);
		OBJ_QUAD[2].Attr<VE_Texture2D>() = XMFLOAT2(0, 0);
		OBJ_QUAD[3].Attr<VE_Texture2D>() = XMFLOAT2(0, 1);
	}
	if (layout->Resolve<VE_Normal>())
	{
		OBJ_QUAD[0].Attr<VE_Normal>() = FORWARD;
		OBJ_QUAD[1].Attr<VE_Normal>() = FORWARD;
		OBJ_QUAD[2].Attr<VE_Normal>() = FORWARD;
		OBJ_QUAD[3].Attr<VE_Normal>() = FORWARD;
	}
	
	const int INDEX_COUNT = 6;
	const int OBJ_QUAD_INDICE[INDEX_COUNT] =
	{
		3,2,1,
		3,1,0
	};


	SetVertice(&OBJ_QUAD, OBJ_QUAD_INDICE, INDEX_COUNT);
	Update(device);
}

