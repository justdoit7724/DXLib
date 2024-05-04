#pragma once
#include "DXUtility.h"

namespace DX
{
	class DXLIB_DLL Buffer
	{
	public:
		Buffer(ID3D11Device* device, D3D11_BUFFER_DESC* desc, void* initValue);
		Buffer(ID3D11Device* device, UINT byteSize);
		

		void SetSRV(ID3D11Device* device, D3D11_SHADER_RESOURCE_VIEW_DESC* srvDesc);
		void SetUAV(ID3D11Device* device, D3D11_UNORDERED_ACCESS_VIEW_DESC* uavDesc);

		void Write(ID3D11DeviceContext* dContext, const void* data);

		ID3D11Buffer* Get() { return m_resource.get(); }
		ID3D11ShaderResourceView* GetSRV();
		ID3D11UnorderedAccessView* GetUAV();

		const D3D11_BUFFER_DESC desc;

	private:


		std::unique_ptr<ID3D11Buffer, Delete_Release> m_resource = nullptr;
		std::unique_ptr<ID3D11ShaderResourceView, Delete_Release> m_srv = nullptr;
		std::unique_ptr<ID3D11UnorderedAccessView, Delete_Release> m_uav = nullptr;
	};
}