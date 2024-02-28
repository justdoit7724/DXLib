#pragma once

#include "Component.h"

namespace DX {
	class DXLIB_DLL DepthStencilState :
		public Component
	{
	private:

		ID3D11DepthStencilState* state;

		UINT refValue;

	public:
		DepthStencilState(ID3D11Device* device, D3D11_DEPTH_STENCIL_DESC* desc);
		~DepthStencilState();
		void Modify(ID3D11Device* device, D3D11_DEPTH_STENCIL_DESC* desc);
		void Apply(const Graphic* graphic) override;
		void SetRefValue(UINT v);
	};
}

