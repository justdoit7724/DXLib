#include "pch.h"
#include "FactoryComponent.h"
#include "Transform.h"

using namespace DX;

std::unique_ptr<Component> DX::FactoryComponent::Create(ComponentKind kind)
{
	std::unique_ptr<Component> newObj=nullptr;

	switch (kind)
	{
	case DX::ComponentKind::Transform:

		break;
	case DX::ComponentKind::Mesh:
		break;
	case DX::ComponentKind::VShader:
		break;
	case DX::ComponentKind::PShader:
		break;
	case DX::ComponentKind::BlendState:
		break;
	case DX::ComponentKind::RasState:
		break;
	case DX::ComponentKind::DSState:
		break;
	case DX::ComponentKind::Collider:
		break;
	default:
		break;
	}

	return nullptr;
}
