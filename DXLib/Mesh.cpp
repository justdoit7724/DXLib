
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

	m_updated = false;
}

void DX::Mesh::SetVertex(int i, Vertex v)
{
	m_vertice[i] = v;

	m_updated = false;
}

void DX::Mesh::SetPos(int i, XMFLOAT3 pos)
{
	m_vertice[i].pos = pos;

	m_updated = false;
}

void DX::Mesh::SetColor(int i, XMFLOAT4 col)
{
	m_vertice[i].color = col;

	m_updated = false;
}

void DX::Mesh::SetColor(DirectX::XMFLOAT4 col)
{
	for (int i = 0; i < m_vertice.size(); ++i)
	{
		m_vertice[i].color = col;
	}

	m_updated = false;
}

Vertex DX::Mesh::GetVertex(int i) const
{
	return m_vertice[i];
}

void Mesh::Clear()
{
	m_vertice.clear();

	m_updated = false;
}


Mesh::Mesh()
	:m_indexBuffer(nullptr), m_vertexBuffer(nullptr), m_indice(nullptr), m_updated(false)
{
	m_primitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

Mesh::Mesh(const Mesh* other)
{
	m_vertice = other->m_vertice;
	m_lMinPt = other->m_lMinPt;
	m_lMaxPt = other->m_lMaxPt;
	SetIndice(other->m_indice.get(), other->m_indexCount);
	m_primitiveType = other->m_primitiveType;
	m_updated = false;
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

	int totalByte = sizeof(int) * indexCount;
	m_indice = std::make_unique<int[]>(totalByte);
	memcpy(m_indice.get(), indice, totalByte);

	m_updated = false;
}

void Mesh::Update(ID3D11Device* device)
{
	if (m_updated)
		return;
	m_updated = true;

	if (m_vertexBuffer)
		m_vertexBuffer->Release();
	m_vertexBuffer = nullptr;
	if (m_indexBuffer)
		m_indexBuffer->Release();
	m_indexBuffer = nullptr;

	if (m_vertice.size())
	{

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
		vb_desc.ByteWidth = sizeof(Vertex) * m_vertice.size();
		vb_desc.CPUAccessFlags = 0;
		vb_desc.MiscFlags = 0;
		vb_desc.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA vb_data;
		vb_data.pSysMem = m_vertice.data();
		ID3D11Buffer* tmpBuffer;
		HRESULT hr = device->CreateBuffer(
			&vb_desc,
			&vb_data,
			&tmpBuffer);
		r_assert(hr);
		m_vertexBuffer = std::unique_ptr<ID3D11Buffer>(tmpBuffer);

		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(UINT) * m_indexCount;
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;
		ibd.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA iinitData;
		iinitData.pSysMem = m_indice.get();
		hr = device->CreateBuffer(&ibd, &iinitData, &tmpBuffer);
		r_assert(hr);
		m_indexBuffer = std::unique_ptr<ID3D11Buffer>(tmpBuffer);
	}
}





void Mesh::Apply(const Graphic* graphic)
{
	Update(graphic->Device());

	if (m_vertexBuffer && m_indexBuffer)
	{
		graphic->DContext()->IASetPrimitiveTopology(m_primitiveType);
		UINT offset = 0;
		UINT verticeSize = sizeof(Vertex);
		auto vb = m_vertexBuffer.get();
		graphic->DContext()->IASetVertexBuffers(0, 1, &vb, &verticeSize, &offset);
		graphic->DContext()->IASetIndexBuffer(m_indexBuffer.get(), DXGI_FORMAT_R32_UINT, 0);

		graphic->DContext()->DrawIndexed(m_indexCount, 0, 0);
	}
}