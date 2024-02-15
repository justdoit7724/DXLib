
#include "pch.h"

#include "QuadMesh.h"
#include "ShaderFormat.h"
#include "MathHelper.h"
#include "Vertex.h"

using namespace DX;

QuadMesh::QuadMesh(ID3D11Device* device, VertexLayout layout)
	: Mesh()
{
	EmplaceBack(4);

	GetVertex(0).Attr<VE_Position3D>() = XMFLOAT3(-0.5, -0.5, 0);
	GetVertex(1).Attr<VE_Position3D>() = XMFLOAT3(-0.5, 0.5, 0);
	GetVertex(2).Attr<VE_Position3D>() = XMFLOAT3(0.5, 0.5, 0);
	GetVertex(3).Attr<VE_Position3D>() = XMFLOAT3(0.5, -0.5, 0);

	if (layout.Resolve<VE_Texture2D>())
	{
		GetVertex(0).Attr<VE_Texture2D>() = XMFLOAT2(1, 1);
		GetVertex(1).Attr<VE_Texture2D>() = XMFLOAT2(1, 0);
		GetVertex(2).Attr<VE_Texture2D>() = XMFLOAT2(0, 0);
		GetVertex(3).Attr<VE_Texture2D>() = XMFLOAT2(0, 1);
	}
	if (layout.Resolve<VE_Normal>())
	{
		GetVertex(0).Attr<VE_Normal>() = FORWARD;
		GetVertex(1).Attr<VE_Normal>() = FORWARD;
		GetVertex(2).Attr<VE_Normal>() = FORWARD;
		GetVertex(3).Attr<VE_Normal>() = FORWARD;
	}
	
	const int INDEX_COUNT = 6;
	const int OBJ_QUAD_INDICE[INDEX_COUNT] =
	{
		3,2,1,
		3,1,0
	};


	SetIndice(OBJ_QUAD_INDICE, INDEX_COUNT);
	Update(device);
}

