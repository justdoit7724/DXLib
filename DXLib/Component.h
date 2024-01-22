#pragma once


namespace DX
{
	class DXLIB_DLL Component
	{
	public:
		Component();

	protected:
		virtual void Apply(ID3D11DeviceContext* dContext)const = 0;
	};
}

