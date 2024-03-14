#include "pch.h"
#include "WorldGraphic.h"
#include "Camera.h"
#include "Transform.h"
#include "Light.h"

using namespace DX;

WorldGraphic::WorldGraphic(HWND hwnd, int msaa)
	:Graphic(hwnd, msaa)
{
	Actor* tmp;
	CreateActor(ActorKind::Camera, &tmp);
	SetMainCamera((Camera*)tmp);
	Camera* cam = (Camera*)tmp;
	cam->transform->SetTranslation(0, 0, -10);
	CreateActor(ActorKind::Light_Direction, &tmp);
	DirectionalLight* light;
	light = (DirectionalLight*)tmp;
	light->SetDir(Normalize(XMFLOAT3(1, -1, 1)));


}
