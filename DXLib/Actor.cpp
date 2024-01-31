#include "pch.h"
#include "Actor.h"

using namespace DX;

Actor::Actor(const Graphic* graphic, ActorKind kind)
	:m_graphic(graphic), isRelease(false), m_kind(kind)
{
	
}

void Actor::Release()
{
	isRelease = true;
}
