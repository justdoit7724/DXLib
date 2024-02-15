#include "pch.h"
#include "Text.h"
#include "Graphic.h"

using namespace DX;

Text::Text(const Graphic* graphic)
	:Actor(graphic, ActorKind::Text)
{
	try
	{

		m_spriteFont = new SpriteFont(graphic->Device(), __FILE__ L"\\..\\DirectXTK\\Font\\Font.spritefont");

		m_spriteBatch = new SpriteBatch(graphic->DContext());
	}
	catch (const std::exception& e)
	{
		std::string error = e.what();
		MessageBoxA(nullptr, error.c_str(), "exception", MB_OK);
	}

	m_x = 0;
	m_y = 0;
	m_scaleX = 1;
	m_scaleY = 1;
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
		m_spriteBatch,
		m_str.c_str(),
		XMFLOAT2(m_x, m_y),
		XMVectorSet(m_colR, m_colG, m_colB,0),
		0.0,
		XMFLOAT2(0,0),
		XMFLOAT2(m_scaleX,m_scaleY)
	);

	m_spriteBatch->End();
}
