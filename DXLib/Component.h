#pragma once
#include "Graphic.h"

namespace DX
{
	class DXLIB_DLL Component
	{
	public:
		Component();

	protected:
		virtual void Apply(const Graphic* graphic) = 0;
	};
}

