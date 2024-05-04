#pragma once
#include "Component.h"

namespace DX {

	enum class ComponentKind
	{
		Transform,
		Mesh,
		VShader,
		PShader,
		BlendState,
		RasState,
		DSState,
		Collider
	};

	class FactoryComponent
	{
	public:

		static std::unique_ptr<Component> Create(ComponentKind kind);
	};
}

