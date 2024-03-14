
#include "pch.h"

#include "DepthStencilState.h"


using namespace DX;


DepthStencilState::DepthStencilState(ID3D11Device* device, D3D11_DEPTH_STENCIL_DESC* desc)
	:refValue(0xff)
{
	D3D11_DEPTH_STENCIL_DESC firstDesc = desc? *desc : CD3D11_DEPTH_STENCIL_DESC(CD3D11_DEFAULT());

	HRESULT hr = device->CreateDepthStencilState(&firstDesc, &state);
	r_assert(hr);
}

void DepthStencilState::Modify(ID3D11Device* device, D3D11_DEPTH_STENCIL_DESC * desc)
{
	state->Release();
	HRESULT hr = device->CreateDepthStencilState(desc, &state);
	r_assert(hr);
}

void DepthStencilState::Apply(const Graphic* graphic)
{
	graphic->DContext()->OMSetDepthStencilState(state, refValue);
}

void DepthStencilState::SetRefValue(UINT v)
{
	refValue = v;
}


DepthStencilState::~DepthStencilState()
{
	state->Release();
}
