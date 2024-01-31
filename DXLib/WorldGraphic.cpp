#include "pch.h"
#include "WorldGraphic.h"

using namespace DX;

WorldGraphic::WorldGraphic(HWND hwnd, int msaa)
	:Graphic(hwnd, msaa)
{
	Actor* tmp;
	CreateActor(ActorKind::Camera, &tmp);
	CreateActor(ActorKind::Light_Direction, &tmp);
	CreateActor(ActorKind::Object, &tmp);


}
