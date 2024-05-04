#pragma once
#include <string>

namespace DX {

	enum class ActorKind {
		Object,
		Camera,
		Light_Direction,
		Light_Point,
		Light_Spot
	};

	class Graphic;
	class DXLIB_DLL Actor
	{
	protected:
		const Graphic* m_graphic;

		friend class Graphic;

		Actor(const Graphic* graphic, ActorKind kind);
		virtual ~Actor() {}

		bool m_isRelease;
		bool m_enable;
		int m_priority;

		
	public:
		virtual void Update() {}
		virtual void Render() {}

		void Release();
		void SetEnable(bool enable);
		void SetPriority(int priority);
		const ActorKind m_kind;


		std::string m_id;
	};
}

