
#include "pch.h"

#include "Mesh.h"
#include "ShaderFormat.h"
#include "Math.h"
#include "Vertex.h"

using namespace DX;

DX::Mesh::Mesh()
	:m_indexBuffer(nullptr), m_vertexBuffer(nullptr), m_indice(nullptr), m_vertice(nullptr), isNeedUpdate(false)
{
	m_primitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}


Mesh::~Mesh()
{
	m_vertexBuffer->Release();
	m_indexBuffer->Release();

	delete[] m_indice;
	delete m_vertice;
}


/*
void Mesh::CalculateTangent(XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, XMFLOAT2 t0, XMFLOAT2 t1, XMFLOAT2 t2, OUT XMFLOAT3* tangent)
{
	XMFLOAT2 dt0 = t1 - t0;
	XMFLOAT2 dt1 = t2 - t0;
	XMFLOAT3 dv0 = v1 - v0;
	XMFLOAT3 dv1 = v2 - v0;
	float determinant = dt0.x * dt1.y - dt0.y * dt1.x;
	*tangent = dv0*(dt1.y / determinant) - dv1*(dt0.y / determinant);
}*/

void Mesh::GetLBound(OUT XMFLOAT3* minPt, OUT XMFLOAT3* maxPt)
{
	*minPt = m_lMinPt;
	*maxPt = m_lMaxPt;
}

Vertex DX::Mesh::GetVertex(int index)
{
	assert(m_vertice->Count() >= index && "vertex index overflow");

	return (*m_vertice)[index];
}

int DX::Mesh::VertexCount()
{
	return m_vertice->Count();
}

void DX::Mesh::SetVertex(int index, Vertex vertex)
{
	(*m_vertice)[index] = vertex;

	isNeedUpdate = true;
}

void DX::Mesh::SetVertice(const Vertice* vertice, const int* indice, int indexCount)
{
	m_indexCount = indexCount;

	m_vertice = new Vertice(vertice->GetLayout());
	*m_vertice = *vertice;

	if (m_indice)
		delete[] m_indice;
	int totalByte = sizeof(int) * indexCount;
	m_indice = new int[totalByte];
	memcpy(m_indice, indice, totalByte);
	isNeedUpdate = true;

}

void DX::Mesh::Update(ID3D11Device* device)
{
	if (isNeedUpdate)
	{
		if(m_vertexBuffer)
			m_vertexBuffer->Release();

		m_lMinPt = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
		m_lMaxPt = XMFLOAT3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		for (int i = 0; i < m_vertice->Count(); ++i)
		{
			m_lMinPt.x = fminf(m_lMinPt.x, (*m_vertice)[i].Attr<VE_Position3D>().x);
			m_lMinPt.y = fminf(m_lMinPt.y, (*m_vertice)[i].Attr<VE_Position3D>().y);
			m_lMinPt.z = fminf(m_lMinPt.z, (*m_vertice)[i].Attr<VE_Position3D>().z);
			m_lMaxPt.x = fmaxf(m_lMaxPt.x, (*m_vertice)[i].Attr<VE_Position3D>().x);
			m_lMaxPt.y = fmaxf(m_lMaxPt.y, (*m_vertice)[i].Attr<VE_Position3D>().y);
			m_lMaxPt.z = fmaxf(m_lMaxPt.z, (*m_vertice)[i].Attr<VE_Position3D>().z);
		}

		D3D11_BUFFER_DESC vb_desc;
		ZeroMemory(&vb_desc, sizeof(D3D11_BUFFER_DESC));
		vb_desc.Usage = D3D11_USAGE_IMMUTABLE;
		vb_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vb_desc.ByteWidth = m_vertice->SizeByte();
		vb_desc.CPUAccessFlags = 0;
		vb_desc.MiscFlags = 0;
		vb_desc.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA vb_data;
		vb_data.pSysMem = m_vertice->GetData();
		HRESULT hr = device->CreateBuffer(
			&vb_desc,
			&vb_data,
			&m_vertexBuffer);
		r_assert(hr);

		if(m_indexBuffer)
			m_indexBuffer->Release();
		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(UINT) * m_indexCount;
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;
		ibd.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA iinitData;
		iinitData.pSysMem = m_indice;
		hr = device->CreateBuffer(&ibd, &iinitData, &m_indexBuffer);
		r_assert(hr);

		isNeedUpdate = false;
	}
}





void Mesh::Apply(ID3D11DeviceContext* dContext)const
{

	dContext->IASetPrimitiveTopology(m_primitiveType);
	UINT offset = 0;
	UINT verticeSize = m_vertice->GetLayout().Size();
	dContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &verticeSize, &offset);
	dContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	dContext->DrawIndexed(m_indexCount, 0, 0);

}