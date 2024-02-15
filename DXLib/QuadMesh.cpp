
#include "pch.h"

#include "QuadMesh.h"
#include "ShaderFormat.h"
#include "MathHelper.h"


using namespace DX;

QuadMesh::QuadMesh(ID3D11Device* device)
	: Mesh()
{
	m_vertice.resize(4);

	m_vertice[0].pos=XMFLOAT3(-0.5, -0.5, 0);
	m_vertice[1].pos=XMFLOAT3(-0.5, 0.5, 0);
	m_vertice[2].pos=XMFLOAT3(0.5, 0.5, 0);
	m_vertice[3].pos=XMFLOAT3(0.5, -0.5, 0);

	m_vertice[0].tex = XMFLOAT2(1, 1);
	m_vertice[1].tex = XMFLOAT2(1, 0);
	m_vertice[2].tex = XMFLOAT2(0, 0);
	m_vertice[3].tex = XMFLOAT2(0, 1);

	m_vertice[0].normal = FORWARD;
	m_vertice[1].normal = FORWARD;
	m_vertice[2].normal = FORWARD;
	m_vertice[3].normal = FORWARD;
	
	
	const int INDEX_COUNT = 6;
	const int OBJ_QUAD_INDICE[INDEX_COUNT] =
	{
		3,2,1,
		3,1,0
	};


	SetIndice(OBJ_QUAD_INDICE, INDEX_COUNT);
	Update(device);
}

