
#include "pch.h"

#include "Mesh.h"
#include "ShaderFormat.h"
#include "MathHelper.h"

#include "Graphic.h"

using namespace DX;

int DX::Mesh::Count() const
{
	return m_vertice.size();
}

void DX::Mesh::Resize(int count)
{
	m_vertice.resize(count);
}

void DX::Mesh::SetVertex(int i, Vertex v)
{
	m_vertice[i] = v;
}

void DX::Mesh::SetPos(int i, XMFLOAT3 pos)
{
	m_vertice[i].pos = pos;
}

void DX::Mesh::SetColor(int i, XMFLOAT4 col)
{
	m_vertice[i].color = col;
}

Vertex DX::Mesh::GetVertex(int i)
{
	return m_vertice[i];
}

void Mesh::Clear()
{
	m_vertice.clear();
}


Mesh::Mesh()
	:m_indexBuffer(nullptr), m_vertexBuffer(nullptr), m_indice(nullptr)
{
	m_primitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}


Mesh::~Mesh()
{
	m_vertexBuffer->Release();
	m_indexBuffer->Release();

	delete[] m_indice;
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


void Mesh::SetIndice(const int* indice, int indexCount)
{
	m_indexCount = indexCount;

	if (m_indice)
		delete[] m_indice;
	int totalByte = sizeof(int) * indexCount;
	m_indice = new int[totalByte];
	memcpy(m_indice, indice, totalByte);

}

void Mesh::Update(ID3D11Device* device)
{
		if(m_vertexBuffer)
			m_vertexBuffer->Release();

		m_lMinPt = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
		m_lMaxPt = XMFLOAT3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		for (int i = 0; i < Count(); ++i)
		{
			m_lMinPt.x = fminf(m_lMinPt.x, m_vertice[i].pos.x);
			m_lMinPt.y = fminf(m_lMinPt.y, m_vertice[i].pos.y);
			m_lMinPt.z = fminf(m_lMinPt.z, m_vertice[i].pos.z);
			m_lMaxPt.x = fmaxf(m_lMaxPt.x, m_vertice[i].pos.x);
			m_lMaxPt.y = fmaxf(m_lMaxPt.y, m_vertice[i].pos.y);
			m_lMaxPt.z = fmaxf(m_lMaxPt.z, m_vertice[i].pos.z);
		}

		D3D11_BUFFER_DESC vb_desc;
		ZeroMemory(&vb_desc, sizeof(D3D11_BUFFER_DESC));
		vb_desc.Usage = D3D11_USAGE_IMMUTABLE;
		vb_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vb_desc.ByteWidth = sizeof(Vertex)*m_vertice.size();
		vb_desc.CPUAccessFlags = 0;
		vb_desc.MiscFlags = 0;
		vb_desc.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA vb_data;
		vb_data.pSysMem = m_vertice.data();
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

}





void Mesh::Apply(ID3D11DeviceContext* dContext)const
{

	dContext->IASetPrimitiveTopology(m_primitiveType);
	UINT offset = 0;
	UINT verticeSize = sizeof(Vertex);
	dContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &verticeSize, &offset);
	dContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	dContext->DrawIndexed(m_indexCount, 0, 0);

}