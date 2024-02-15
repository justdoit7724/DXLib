
#include "pch.h"

#include "Mesh.h"
#include "ShaderFormat.h"
#include "LineMesh.h"

using namespace DX;

LineMesh::LineMesh()
{
	m_primitiveType = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
}


