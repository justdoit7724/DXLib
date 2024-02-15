
#include "pch.h"

#include "Mesh.h"
#include "ShaderFormat.h"
#include "MathHelper.h"
#include "Vertex.h"
#include "Graphic.h"

using namespace DX;


VertexLayout::Element::Element(VertexElementType type, int offset)
	:m_type(type), m_offset(offset)
{
}
int VertexLayout::Element::GetOffsetAfter()const
{
	return m_offset + Size();
}
int VertexLayout::Element::GetOffset()const
{
	return m_offset;
}
int VertexLayout::Element::Size() const
{
	return SizeOf(m_type);
}

int VertexLayout::Element::SizeOf(VertexElementType type)
{
	switch (type)
	{
	case VE_Position2D:
		return sizeof(Map< VE_Position2D>::SysType);
	case VE_Texture2D:
		return sizeof(Map<VE_Texture2D>::SysType);
	case VE_Position3D:
		return sizeof(Map<VE_Position3D>::SysType);
	case VE_Normal:
		return sizeof(Map<VE_Normal>::SysType);
	case VE_Float3Color:
		return sizeof(Map<VE_Float3Color>::SysType);
	case VE_Float4Color:
		return sizeof(Map<VE_Float4Color>::SysType);
	case VE_BGRAColor:
		return sizeof(Map<VE_BGRAColor>::SysType);
	}

	assert("Wrong Element Type" && false);
}

VertexElementType VertexLayout::Element::GetType() const
{
	return m_type;
}

D3D11_INPUT_ELEMENT_DESC VertexLayout::Element::GetDesc() const
{
	switch (m_type)
	{
	case VE_Position2D:
		return GenerateDesc<VE_Position2D>(m_offset);
	case VE_Position3D:
		return GenerateDesc<VE_Position3D>(m_offset);
	case VE_Texture2D:
		return GenerateDesc<VE_Texture2D>(m_offset);
	case VE_Normal:
		return GenerateDesc<VE_Normal>(m_offset);
	case VE_Float3Color:
		return GenerateDesc<VE_Float3Color>(m_offset);
	case VE_Float4Color:
		return GenerateDesc<VE_Float4Color>(m_offset);
	case VE_BGRAColor:
		return GenerateDesc<VE_BGRAColor>(m_offset);
	}

	assert("wrong Element Type" && false);
}


int VertexLayout::Count() const
{
	return m_elements.size();
}

void VertexLayout::Clear()
{
	m_elements.clear();
}

const VertexLayout::Element* VertexLayout::ResolveByIndex(unsigned int i)const
{
	return &m_elements[i];
}
VertexLayout& VertexLayout::Append(VertexElementType type)
{
	m_elements.emplace_back(type, Size());
	return *this;
}
int VertexLayout::Size() const
{
	if (m_elements.empty())
		return 0;

	return m_elements.back().GetOffsetAfter();
}
std::vector<D3D11_INPUT_ELEMENT_DESC> VertexLayout::GetLayout() const
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
	for (const auto& elem : m_elements)
	{
		descs.push_back(elem.GetDesc());
	}

	return descs;
}




Vertex::Vertex(char* data, const VertexLayout& layout)
	:m_data(data), m_layout(layout) {}

const VertexLayout& Mesh::GetLayout() const
{
	return m_layout;
}
const char* Mesh::GetData() const
{
	return m_buffer.data();
}
int Mesh::SizeByte() const
{
	return m_buffer.size();
}
int Mesh::Count() const
{
	return m_buffer.size() / m_layout.Size();
}

void Mesh::EmplaceBack(int count)
{
	assert(m_layout.Count() > 0 && count > 0 && "layout is empty");

	m_buffer.resize(m_buffer.size() + m_layout.Size() * count);
}

Vertex Mesh::Front()
{
	if (m_buffer.empty())
		assert("VertexBuffer is empty" && false);

	return Vertex(m_buffer.data(), m_layout);
}
Vertex Mesh::Back()
{
	if (m_buffer.empty())
		assert("VertexBuffer is empty" && false);

	return Vertex(m_buffer.data() + m_buffer.size() - m_layout.Size(), m_layout);
}
Vertex Mesh::GetVertex(int i)
{
	assert(i < Count());
	return Vertex(m_buffer.data() + m_layout.Size() * i, m_layout);
}

void Mesh::Clear()
{
	m_buffer.clear();
}


Mesh::Mesh()
	:m_indexBuffer(nullptr), m_vertexBuffer(nullptr), m_indice(nullptr), isNeedUpdate(false)
{
	m_primitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_layout = D3DLayout_Std();
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
	isNeedUpdate = true;

}

void Mesh::Update(ID3D11Device* device)
{
	if (isNeedUpdate)
	{
		if(m_vertexBuffer)
			m_vertexBuffer->Release();

		m_lMinPt = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
		m_lMaxPt = XMFLOAT3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		for (int i = 0; i < Count(); ++i)
		{
			m_lMinPt.x = fminf(m_lMinPt.x, GetVertex(i).Attr<VE_Position3D>().x);
			m_lMinPt.y = fminf(m_lMinPt.y, GetVertex(i).Attr<VE_Position3D>().y);
			m_lMinPt.z = fminf(m_lMinPt.z, GetVertex(i).Attr<VE_Position3D>().z);
			m_lMaxPt.x = fmaxf(m_lMaxPt.x, GetVertex(i).Attr<VE_Position3D>().x);
			m_lMaxPt.y = fmaxf(m_lMaxPt.y, GetVertex(i).Attr<VE_Position3D>().y);
			m_lMaxPt.z = fmaxf(m_lMaxPt.z, GetVertex(i).Attr<VE_Position3D>().z);
		}

		D3D11_BUFFER_DESC vb_desc;
		ZeroMemory(&vb_desc, sizeof(D3D11_BUFFER_DESC));
		vb_desc.Usage = D3D11_USAGE_IMMUTABLE;
		vb_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vb_desc.ByteWidth = SizeByte();
		vb_desc.CPUAccessFlags = 0;
		vb_desc.MiscFlags = 0;
		vb_desc.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA vb_data;
		vb_data.pSysMem = GetData();
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
	UINT verticeSize = GetLayout().Size();
	dContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &verticeSize, &offset);
	dContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	dContext->DrawIndexed(m_indexCount, 0, 0);

}