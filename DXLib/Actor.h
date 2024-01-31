#pragma once

namespace DX {

	enum class ActorKind {
		Object,
		Camera,
		Light_Direction,
		Light_Point,
		Light_Spot,
		Text
	};

	class Graphic;
	class DXLIB_DLL Actor
	{
	protected:
		const Graphic* m_graphic;

		friend class Graphic;

		Actor(const Graphic* graphic, ActorKind kind);

		bool isRelease;
		
	public:
		virtual void Update() {}
		virtual void Render() {}

		void Release();
		const ActorKind m_kind;
	};
}

