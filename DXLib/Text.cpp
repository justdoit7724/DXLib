#include "pch.h"
#include "Text.h"
#include "Graphic.h"

using namespace DX;

Text::Text(const Graphic* graphic)
	:Actor(graphic, ActorKind::Text)
{
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(graphic->Device(), L"DirectXTK\\Font\\Font.spritefont");

	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(graphic->DContext());
}

void Text::SetStr(std::string str)
{
	m_str = str;
}

void Text::SetPos(float x, float y)
{
	m_x = x;
	m_y = y;
}

void Text::SetColor(float r, float g, float b)
{
	m_colR = r;
	m_colG = g;
	m_colB = b;
}

void Text::SetScale(float x, float y)
{
	m_scaleX = x;
	m_scaleY = y;
}

void Text::Render()
{
	m_spriteBatch->Begin();

	m_spriteFont->DrawString(
		m_spriteBatch.get(),
		m_str.c_str(),
		XMFLOAT2(m_x, m_y),
		XMVectorSet(m_colR, m_colG, m_colB,0),
		0.0,
		XMFLOAT2(0,0),
		XMFLOAT2(m_scaleX,m_scaleY)
	);

	m_spriteBatch->End();
}
