#include "pch.h"
#include "Vertex.h"

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
	:m_data(data), m_layout(layout){}

Vertice::Vertice(VertexLayout layout)
	:m_layout(std::move(layout)){}

const VertexLayout& Vertice::GetLayout() const
{
	return m_layout;
}
const char* Vertice::GetData() const
{
	return m_buffer.data();
}
int Vertice::SizeByte() const
{
	return m_buffer.size();
}
int Vertice::Count() const
{
	return m_buffer.size() / m_layout.Size();
}
	
void DX::Vertice::EmplaceBack()
{
	if (m_layout.Count() == 0)
		assert("layout is empty" && false);

	m_buffer.resize(m_buffer.size() + m_layout.Size());
}

Vertex Vertice::Front()
{
	if (m_buffer.empty())
		assert("VertexBuffer is empty" && false);

	return Vertex(m_buffer.data(), m_layout);
}
Vertex Vertice::Back()
{
	if (m_buffer.empty())
		assert("VertexBuffer is empty" && false);

	return Vertex(m_buffer.data() + m_buffer.size() - m_layout.Size() ,m_layout);
}
Vertex Vertice::operator[](int i)
{
	assert(i < Count());
	return Vertex(m_buffer.data() + m_layout.Size() * i,m_layout );
}

void DX::Vertice::Clear()
{
	m_buffer.clear();
}
