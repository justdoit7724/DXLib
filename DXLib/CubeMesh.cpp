#include "pch.h"
#include "CubeMesh.h"

#include "ShaderFormat.h"
#include "MathHelper.h"
#include "Graphic.h"

using namespace DX;

const int INDEX_COUNT = 36;
const int OBJ_CUBE_INDICE[INDEX_COUNT] =
{
	0,1,2,
	0,2,3,
	4,5,6,
	4,6,7,
	8,9,10,
	8,10,11,
	12,13,14,
	12,14,15,
	16,17,18,
	16,18,19,
	20,21,22,
	20,22,23
};

DX::CubeMesh::CubeMesh(ID3D11Device* device)
{
	auto layout = D3DLayout_Std();

	for (int i = 0; i < 30; ++i)
	{
		EmplaceBack();
	}
	if (layout.Resolve<VE_Position3D>())
	{
		GetVertex(0).Attr< VE_Position3D>() = XMFLOAT3(-0.5, -0.5, -0.5);
		GetVertex(1).Attr< VE_Position3D>() = XMFLOAT3(-0.5, 0.5, -0.5);
		GetVertex(2).Attr< VE_Position3D>() = XMFLOAT3(0.5, 0.5, -0.5);
		GetVertex(3).Attr< VE_Position3D>() = XMFLOAT3(0.5, -0.5, -0.5);
		GetVertex(4).Attr< VE_Position3D>() = XMFLOAT3(0.5, -0.5, -0.5);
		GetVertex(5).Attr< VE_Position3D>() = XMFLOAT3(0.5, 0.5, -0.5);
		GetVertex(6).Attr< VE_Position3D>() = XMFLOAT3(0.5, 0.5, 0.5);
		GetVertex(7).Attr< VE_Position3D>() = XMFLOAT3(0.5, -0.5, 0.5);
		GetVertex(8).Attr< VE_Position3D>() = XMFLOAT3(0.5, -0.5, 0.5);
		GetVertex(9).Attr< VE_Position3D>() = XMFLOAT3(0.5, 0.5, 0.5);
		GetVertex(10).Attr< VE_Position3D>() = XMFLOAT3(-0.5, 0.5, 0.5);
		GetVertex(11).Attr< VE_Position3D>() = XMFLOAT3(-0.5, -0.5, 0.5);
		GetVertex(12).Attr< VE_Position3D>() = XMFLOAT3(-0.5, -0.5, 0.5);
		GetVertex(13).Attr< VE_Position3D>() = XMFLOAT3(-0.5, 0.5, 0.5);
		GetVertex(14).Attr< VE_Position3D>() = XMFLOAT3(-0.5, 0.5, -0.5);
		GetVertex(15).Attr< VE_Position3D>() = XMFLOAT3(-0.5, -0.5, -0.5);
		GetVertex(16).Attr< VE_Position3D>() = XMFLOAT3(-0.5, 0.5, -0.5);
		GetVertex(17).Attr< VE_Position3D>() = XMFLOAT3(-0.5, 0.5, 0.5);
		GetVertex(18).Attr< VE_Position3D>() = XMFLOAT3(0.5, 0.5, 0.5);
		GetVertex(19).Attr< VE_Position3D>() = XMFLOAT3(0.5, 0.5, -0.5);
		GetVertex(20).Attr< VE_Position3D>() = XMFLOAT3(-0.5, -0.5, 0.5);
		GetVertex(21).Attr< VE_Position3D>() = XMFLOAT3(-0.5, -0.5, -0.5);
		GetVertex(22).Attr< VE_Position3D>() = XMFLOAT3(0.5, -0.5, -0.5);
		GetVertex(23).Attr< VE_Position3D>() = XMFLOAT3(0.5, -0.5, 0.5);
		
	}
	if (layout.Resolve<VE_Texture2D>())
	{
		GetVertex(0).Attr< VE_Texture2D>() = XMFLOAT2(0, 1);
		GetVertex(1).Attr< VE_Texture2D>() = XMFLOAT2(0, 0);
		GetVertex(2).Attr< VE_Texture2D>() = XMFLOAT2(1, 0);
		GetVertex(3).Attr< VE_Texture2D>() = XMFLOAT2(1, 1);
		GetVertex(4).Attr< VE_Texture2D>() = XMFLOAT2(0, 1);
		GetVertex(5).Attr< VE_Texture2D>() = XMFLOAT2(0, 0);
		GetVertex(6).Attr< VE_Texture2D>() = XMFLOAT2(1, 0);
		GetVertex(7).Attr< VE_Texture2D>() = XMFLOAT2(1, 1);
		GetVertex(8).Attr< VE_Texture2D>() = XMFLOAT2(0, 1);
		GetVertex(9).Attr< VE_Texture2D>() = XMFLOAT2(0, 0);
		GetVertex(10).Attr< VE_Texture2D>() = XMFLOAT2(1, 0);
		GetVertex(11).Attr< VE_Texture2D>() = XMFLOAT2(1, 1);
		GetVertex(12).Attr< VE_Texture2D>() = XMFLOAT2(0, 1);
		GetVertex(13).Attr< VE_Texture2D>() = XMFLOAT2(0, 0);
		GetVertex(14).Attr< VE_Texture2D>() = XMFLOAT2(1, 0);
		GetVertex(15).Attr< VE_Texture2D>() = XMFLOAT2(1, 1);
		GetVertex(16).Attr< VE_Texture2D>() = XMFLOAT2(0, 1);
		GetVertex(17).Attr< VE_Texture2D>() = XMFLOAT2(0, 0);
		GetVertex(18).Attr< VE_Texture2D>() = XMFLOAT2(1, 0);
		GetVertex(19).Attr< VE_Texture2D>() = XMFLOAT2(1, 1);
		GetVertex(20).Attr< VE_Texture2D>() = XMFLOAT2(0, 1);
		GetVertex(21).Attr< VE_Texture2D>() = XMFLOAT2(0, 0);
		GetVertex(22).Attr< VE_Texture2D>() = XMFLOAT2(1, 0);
		GetVertex(23).Attr< VE_Texture2D>() = XMFLOAT2(1, 1);
	}
	if (layout.Resolve<VE_Normal>())
	{
		GetVertex(0).Attr< VE_Normal>() = BACKWARD;
		GetVertex(1).Attr< VE_Normal>() = BACKWARD;
		GetVertex(2).Attr< VE_Normal>() = BACKWARD;
		GetVertex(3).Attr< VE_Normal>() = BACKWARD;
		GetVertex(4).Attr< VE_Normal>() = RIGHT;
		GetVertex(5).Attr< VE_Normal>() = RIGHT;
		GetVertex(6).Attr< VE_Normal>() = RIGHT;
		GetVertex(7).Attr< VE_Normal>() = RIGHT;
		GetVertex(8).Attr< VE_Normal>() = FORWARD;
		GetVertex(9).Attr< VE_Normal>() = FORWARD;
		GetVertex(10).Attr< VE_Normal>() = FORWARD;
		GetVertex(11).Attr< VE_Normal>() = FORWARD;
		GetVertex(12).Attr< VE_Normal>() = RIGHT;
		GetVertex(13).Attr< VE_Normal>() = RIGHT;
		GetVertex(14).Attr< VE_Normal>() = RIGHT;
		GetVertex(15).Attr< VE_Normal>() = RIGHT;
		GetVertex(16).Attr< VE_Normal>() = UP;
		GetVertex(17).Attr< VE_Normal>() = UP;
		GetVertex(18).Attr< VE_Normal>() = UP;
		GetVertex(19).Attr< VE_Normal>() = UP;
		GetVertex(20).Attr< VE_Normal>() = DOWN;
		GetVertex(21).Attr< VE_Normal>() = DOWN;
		GetVertex(22).Attr< VE_Normal>() = DOWN;
		GetVertex(23).Attr< VE_Normal>() = DOWN;
	}
	
	SetIndice(OBJ_CUBE_INDICE, INDEX_COUNT);
	Update(device);
}
