#include "pch.h"
#include "Actor.h"

using namespace DX;


DX::Actor::Actor(const Graphic* graphic, ActorKind kind)
	:m_graphic(graphic), m_isRelease(false), m_kind(kind), m_enable(true), m_priority(0)
{
	
}


void Actor::Release()
{
	m_isRelease = true;
}

void DX::Actor::SetEnable(bool enable)
{
	m_enable = enable;
}

void DX::Actor::SetPriority(int priority)
{
	m_priority = priority;
}
