#include "pch.h"
#include "CubeMesh.h"

#include "ShaderFormat.h"
#include "Math.h"
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

	Vertice OBJ_CUBE(layout);
	
	for (int i = 0; i < 30; ++i)
	{
		OBJ_CUBE.EmplaceBack();
	}
	if (layout.Resolve<VE_Position3D>())
	{
		OBJ_CUBE[0].Attr< VE_Position3D>() = XMFLOAT3(-0.5, -0.5, -0.5);
		OBJ_CUBE[1].Attr< VE_Position3D>() = XMFLOAT3(-0.5, 0.5, -0.5);
		OBJ_CUBE[2].Attr< VE_Position3D>() = XMFLOAT3(0.5, 0.5, -0.5);
		OBJ_CUBE[3].Attr< VE_Position3D>() = XMFLOAT3(0.5, -0.5, -0.5);
		OBJ_CUBE[4].Attr< VE_Position3D>() = XMFLOAT3(0.5, -0.5, -0.5);
		OBJ_CUBE[5].Attr< VE_Position3D>() = XMFLOAT3(0.5, 0.5, -0.5);
		OBJ_CUBE[6].Attr< VE_Position3D>() = XMFLOAT3(0.5, 0.5, 0.5);
		OBJ_CUBE[7].Attr< VE_Position3D>() = XMFLOAT3(0.5, -0.5, 0.5);
		OBJ_CUBE[8].Attr< VE_Position3D>() = XMFLOAT3(0.5, -0.5, 0.5);
		OBJ_CUBE[9].Attr< VE_Position3D>() = XMFLOAT3(0.5, 0.5, 0.5);
		OBJ_CUBE[10].Attr< VE_Position3D>() = XMFLOAT3(-0.5, 0.5, 0.5);
		OBJ_CUBE[11].Attr< VE_Position3D>() = XMFLOAT3(-0.5, -0.5, 0.5);
		OBJ_CUBE[12].Attr< VE_Position3D>() = XMFLOAT3(-0.5, -0.5, 0.5);
		OBJ_CUBE[13].Attr< VE_Position3D>() = XMFLOAT3(-0.5, 0.5, 0.5);
		OBJ_CUBE[14].Attr< VE_Position3D>() = XMFLOAT3(-0.5, 0.5, -0.5);
		OBJ_CUBE[15].Attr< VE_Position3D>() = XMFLOAT3(-0.5, -0.5, -0.5);
		OBJ_CUBE[16].Attr< VE_Position3D>() = XMFLOAT3(-0.5, 0.5, -0.5);
		OBJ_CUBE[17].Attr< VE_Position3D>() = XMFLOAT3(-0.5, 0.5, 0.5);
		OBJ_CUBE[18].Attr< VE_Position3D>() = XMFLOAT3(0.5, 0.5, 0.5);
		OBJ_CUBE[19].Attr< VE_Position3D>() = XMFLOAT3(0.5, 0.5, -0.5);
		OBJ_CUBE[20].Attr< VE_Position3D>() = XMFLOAT3(-0.5, -0.5, 0.5);
		OBJ_CUBE[21].Attr< VE_Position3D>() = XMFLOAT3(-0.5, -0.5, -0.5);
		OBJ_CUBE[22].Attr< VE_Position3D>() = XMFLOAT3(0.5, -0.5, -0.5);
		OBJ_CUBE[23].Attr< VE_Position3D>() = XMFLOAT3(0.5, -0.5, 0.5);
		
	}
	if (layout.Resolve<VE_Texture2D>())
	{
		OBJ_CUBE[0].Attr< VE_Texture2D>() = XMFLOAT2(0, 1);
		OBJ_CUBE[1].Attr< VE_Texture2D>() = XMFLOAT2(0, 0);
		OBJ_CUBE[2].Attr< VE_Texture2D>() = XMFLOAT2(1, 0);
		OBJ_CUBE[3].Attr< VE_Texture2D>() = XMFLOAT2(1, 1);
		OBJ_CUBE[4].Attr< VE_Texture2D>() = XMFLOAT2(0, 1);
		OBJ_CUBE[5].Attr< VE_Texture2D>() = XMFLOAT2(0, 0);
		OBJ_CUBE[6].Attr< VE_Texture2D>() = XMFLOAT2(1, 0);
		OBJ_CUBE[7].Attr< VE_Texture2D>() = XMFLOAT2(1, 1);
		OBJ_CUBE[8].Attr< VE_Texture2D>() = XMFLOAT2(0, 1);
		OBJ_CUBE[9].Attr< VE_Texture2D>() = XMFLOAT2(0, 0);
		OBJ_CUBE[10].Attr< VE_Texture2D>() = XMFLOAT2(1, 0);
		OBJ_CUBE[11].Attr< VE_Texture2D>() = XMFLOAT2(1, 1);
		OBJ_CUBE[12].Attr< VE_Texture2D>() = XMFLOAT2(0, 1);
		OBJ_CUBE[13].Attr< VE_Texture2D>() = XMFLOAT2(0, 0);
		OBJ_CUBE[14].Attr< VE_Texture2D>() = XMFLOAT2(1, 0);
		OBJ_CUBE[15].Attr< VE_Texture2D>() = XMFLOAT2(1, 1);
		OBJ_CUBE[16].Attr< VE_Texture2D>() = XMFLOAT2(0, 1);
		OBJ_CUBE[17].Attr< VE_Texture2D>() = XMFLOAT2(0, 0);
		OBJ_CUBE[18].Attr< VE_Texture2D>() = XMFLOAT2(1, 0);
		OBJ_CUBE[19].Attr< VE_Texture2D>() = XMFLOAT2(1, 1);
		OBJ_CUBE[20].Attr< VE_Texture2D>() = XMFLOAT2(0, 1);
		OBJ_CUBE[21].Attr< VE_Texture2D>() = XMFLOAT2(0, 0);
		OBJ_CUBE[22].Attr< VE_Texture2D>() = XMFLOAT2(1, 0);
		OBJ_CUBE[23].Attr< VE_Texture2D>() = XMFLOAT2(1, 1);
	}
	if (layout.Resolve<VE_Normal>())
	{
		OBJ_CUBE[0].Attr< VE_Normal>() = -FORWARD;
		OBJ_CUBE[1].Attr< VE_Normal>() = -FORWARD;
		OBJ_CUBE[2].Attr< VE_Normal>() = -FORWARD;
		OBJ_CUBE[3].Attr< VE_Normal>() = -FORWARD;
		OBJ_CUBE[4].Attr< VE_Normal>() = RIGHT;
		OBJ_CUBE[5].Attr< VE_Normal>() = RIGHT;
		OBJ_CUBE[6].Attr< VE_Normal>() = RIGHT;
		OBJ_CUBE[7].Attr< VE_Normal>() = RIGHT;
		OBJ_CUBE[8].Attr< VE_Normal>() = FORWARD;
		OBJ_CUBE[9].Attr< VE_Normal>() = FORWARD;
		OBJ_CUBE[10].Attr< VE_Normal>() = FORWARD;
		OBJ_CUBE[11].Attr< VE_Normal>() = FORWARD;
		OBJ_CUBE[12].Attr< VE_Normal>() = RIGHT;
		OBJ_CUBE[13].Attr< VE_Normal>() = RIGHT;
		OBJ_CUBE[14].Attr< VE_Normal>() = RIGHT;
		OBJ_CUBE[15].Attr< VE_Normal>() = RIGHT;
		OBJ_CUBE[16].Attr< VE_Normal>() = UP;
		OBJ_CUBE[17].Attr< VE_Normal>() = UP;
		OBJ_CUBE[18].Attr< VE_Normal>() = UP;
		OBJ_CUBE[19].Attr< VE_Normal>() = UP;
		OBJ_CUBE[20].Attr< VE_Normal>() = -UP;
		OBJ_CUBE[21].Attr< VE_Normal>() = -UP;
		OBJ_CUBE[22].Attr< VE_Normal>() = -UP;
		OBJ_CUBE[23].Attr< VE_Normal>() = -UP;
	}
	
	SetVertice(&OBJ_CUBE, OBJ_CUBE_INDICE, INDEX_COUNT);
	Update(device);
}
