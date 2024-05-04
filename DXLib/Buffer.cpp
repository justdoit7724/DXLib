
#include "pch.h"
#include "Buffer.h"

using namespace DX;
Buffer::Buffer(ID3D11Device* device, D3D11_BUFFER_DESC* desc, void * initValue)
	:desc(*desc)
{
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = initValue;

	ID3D11Buffer* tmp=nullptr;
	HRESULT hr = device->CreateBuffer(
			desc,
		!initValue? nullptr : &data,
			&tmp);
	r_assert(hr);

	m_resource = std::unique_ptr<ID3D11Buffer, Delete_Release>(tmp);
}

UINT SizeCB(UINT byteSize)
{
	return (15 + byteSize - (byteSize - 1) % 16);
}
Buffer::Buffer(ID3D11Device* device, UINT byteSize)
	:desc(CD3D11_BUFFER_DESC(SizeCB(byteSize), D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE, 0, 0))
{
	ID3D11Buffer* tmp=nullptr;
	HRESULT hr = device->CreateBuffer(&desc, nullptr, &tmp);
	r_assert(hr);
	m_resource = std::unique_ptr<ID3D11Buffer, Delete_Release>(tmp);
}



void Buffer::SetSRV(ID3D11Device* device, D3D11_SHADER_RESOURCE_VIEW_DESC* srvDesc)
{
	ID3D11ShaderResourceView* tmp;
	HRESULT hr = device->CreateShaderResourceView(
			m_resource.get(),
			srvDesc,
			&tmp);
	r_assert(hr);

	m_srv = std::unique_ptr<ID3D11ShaderResourceView, Delete_Release>(tmp);
}
void Buffer::SetUAV(ID3D11Device* device, D3D11_UNORDERED_ACCESS_VIEW_DESC * uavDesc)
{
	ID3D11UnorderedAccessView* tmp;
	HRESULT hr = device->CreateUnorderedAccessView(
			m_resource.get(),
			uavDesc,
			&tmp);
	r_assert(hr);
	m_uav = std::unique_ptr<ID3D11UnorderedAccessView, Delete_Release>(tmp);
}

void Buffer::Write(ID3D11DeviceContext* dContext, const void * data)
{
	D3D11_MAPPED_SUBRESOURCE mappedData;

	dContext->Map(m_resource.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	CopyMemory(mappedData.pData, data, desc.ByteWidth);
	dContext->Unmap(m_resource.get(), 0);
}

ID3D11ShaderResourceView* DX::Buffer::GetSRV()
{
	return m_srv.get();
}

ID3D11UnorderedAccessView* DX::Buffer::GetUAV()
{
	return m_uav.get();
}
