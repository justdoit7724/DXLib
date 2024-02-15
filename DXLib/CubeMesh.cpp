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
	m_vertice.resize(24);
	
	m_vertice[0].pos= XMFLOAT3(-0.5, -0.5, -0.5);
	m_vertice[1].pos= XMFLOAT3(-0.5, 0.5, -0.5);
	m_vertice[2].pos= XMFLOAT3(0.5, 0.5, -0.5);
	m_vertice[3].pos= XMFLOAT3(0.5, -0.5, -0.5);
	m_vertice[4].pos= XMFLOAT3(0.5, -0.5, -0.5);
	m_vertice[5].pos= XMFLOAT3(0.5, 0.5, -0.5);
	m_vertice[6].pos= XMFLOAT3(0.5, 0.5, 0.5);
	m_vertice[7].pos= XMFLOAT3(0.5, -0.5, 0.5);
	m_vertice[8].pos= XMFLOAT3(0.5, -0.5, 0.5);
	m_vertice[9].pos= XMFLOAT3(0.5, 0.5, 0.5);
	m_vertice[10].pos= XMFLOAT3(-0.5, 0.5, 0.5);
	m_vertice[11].pos= XMFLOAT3(-0.5, -0.5, 0.5);
	m_vertice[12].pos= XMFLOAT3(-0.5, -0.5, 0.5);
	m_vertice[13].pos= XMFLOAT3(-0.5, 0.5, 0.5);
	m_vertice[14].pos= XMFLOAT3(-0.5, 0.5, -0.5);
	m_vertice[15].pos= XMFLOAT3(-0.5, -0.5, -0.5);
	m_vertice[16].pos= XMFLOAT3(-0.5, 0.5, -0.5);
	m_vertice[17].pos= XMFLOAT3(-0.5, 0.5, 0.5);
	m_vertice[18].pos= XMFLOAT3(0.5, 0.5, 0.5);
	m_vertice[19].pos= XMFLOAT3(0.5, 0.5, -0.5);
	m_vertice[20].pos= XMFLOAT3(-0.5, -0.5, 0.5);
	m_vertice[21].pos= XMFLOAT3(-0.5, -0.5, -0.5);
	m_vertice[22].pos= XMFLOAT3(0.5, -0.5, -0.5);
	m_vertice[23].pos= XMFLOAT3(0.5, -0.5, 0.5);
	
	
	m_vertice[0].tex= XMFLOAT2(0, 1);
	m_vertice[1].tex= XMFLOAT2(0, 0);
	m_vertice[2].tex= XMFLOAT2(1, 0);
	m_vertice[3].tex= XMFLOAT2(1, 1);
	m_vertice[4].tex= XMFLOAT2(0, 1);
	m_vertice[5].tex= XMFLOAT2(0, 0);
	m_vertice[6].tex= XMFLOAT2(1, 0);
	m_vertice[7].tex= XMFLOAT2(1, 1);
	m_vertice[8].tex= XMFLOAT2(0, 1);
	m_vertice[9].tex= XMFLOAT2(0, 0);
	m_vertice[10].tex= XMFLOAT2(1, 0);
	m_vertice[11].tex= XMFLOAT2(1, 1);
	m_vertice[12].tex= XMFLOAT2(0, 1);
	m_vertice[13].tex= XMFLOAT2(0, 0);
	m_vertice[14].tex= XMFLOAT2(1, 0);
	m_vertice[15].tex= XMFLOAT2(1, 1);
	m_vertice[16].tex= XMFLOAT2(0, 1);
	m_vertice[17].tex= XMFLOAT2(0, 0);
	m_vertice[18].tex= XMFLOAT2(1, 0);
	m_vertice[19].tex= XMFLOAT2(1, 1);
	m_vertice[20].tex= XMFLOAT2(0, 1);
	m_vertice[21].tex= XMFLOAT2(0, 0);
	m_vertice[22].tex= XMFLOAT2(1, 0);
	m_vertice[23].tex= XMFLOAT2(1, 1);
	
	m_vertice[0].normal= BACKWARD;
	m_vertice[1].normal= BACKWARD;
	m_vertice[2].normal= BACKWARD;
	m_vertice[3].normal= BACKWARD;
	m_vertice[4].normal= RIGHT;
	m_vertice[5].normal= RIGHT;
	m_vertice[6].normal= RIGHT;
	m_vertice[7].normal= RIGHT;
	m_vertice[8].normal= FORWARD;
	m_vertice[9].normal= FORWARD;
	m_vertice[10].normal = FORWARD;
	m_vertice[11].normal = FORWARD;
	m_vertice[12].normal = RIGHT;
	m_vertice[13].normal = RIGHT;
	m_vertice[14].normal = RIGHT;
	m_vertice[15].normal = RIGHT;
	m_vertice[16].normal = UP;
	m_vertice[17].normal = UP;
	m_vertice[18].normal = UP;
	m_vertice[19].normal = UP;
	m_vertice[20].normal = DOWN;
	m_vertice[21].normal = DOWN;
	m_vertice[22].normal = DOWN;
	m_vertice[23].normal = DOWN;
	
	SetIndice(OBJ_CUBE_INDICE, INDEX_COUNT);
	Update(device);
}
