#pragma once

namespace DX {

	class Graphic;
	class DXLIB_DLL Actor
	{
	protected:
		const Graphic* m_graphic;

		friend class Graphic;

		Actor(const Graphic* graphic);
		
	public:
		virtual void Update() {}
	};
}

