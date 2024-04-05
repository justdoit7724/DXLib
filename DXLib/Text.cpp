#include "pch.h"
#include "Text.h"
#include "Graphic.h"
#include "Camera.h"

using namespace DX;

#define TEXT_ALIGN_MARGIN_X 7
#define TEXT_ALIGN_MARGIN_Y 18

Text::Text(const Graphic* graphic)
	:Actor(graphic, ActorKind::Text), m_align(Left)
{
	m_spriteFont = new SpriteFont(graphic->Device(), __FILE__ L"\\..\\DirectXTK\\Font\\Font.spritefont");

	m_spriteBatch = new SpriteBatch(graphic->DContext());

	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_scaleX = 1;
	m_scaleY = 1;
	SetColor(0, 0, 0);
}

void Text::SetAlign(Align align)
{
	m_align = align;
}

void Text::SetStr(std::string str)
{
	m_str = str;
}

void Text::SetPos(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
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

void Text::Set3D(bool is3D)
{
	m_is3D = is3D;
}

void Text::Render()
{
	if (!m_enable)
		return;

	m_spriteBatch->Begin();

	auto cam =(Camera*)m_graphic->MainCamera();
	XMMATRIX vp = cam->VMat() * cam->ProjMat();


	XMFLOAT4 textPos = XMFLOAT4(m_x, m_y, m_z, 1);
	if (m_is3D)
	{
		textPos = Multiply(textPos, vp);
		textPos = Div(textPos, textPos.w);

		RECT rc;
		GetWindowRect(m_graphic->GetHWND(), &rc);
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;

		const XMMATRIX textMat = XMMATRIX(
			width / 2.0f, 0, 0, 0,
			0, -height / 2.0f, 0, 0,
			0, 0, 1, 0,
			width / 2.0f, height / 2.0f, 0, 1);

		textPos = Multiply(textPos, textMat);
	}

	textPos.x += m_scaleX * TEXT_ALIGN_MARGIN_X;
	textPos.y += m_scaleY * TEXT_ALIGN_MARGIN_Y;
	switch (m_align)
	{
		case Left:
			break;
		case Center:
			textPos.x -= m_scaleX * TEXT_ALIGN_MARGIN_X * m_str.size();
			break;
		case Right:
			textPos.x -= m_scaleX * TEXT_ALIGN_MARGIN_X*2 * m_str.size();
			break;
	}

	m_spriteFont->DrawString(
		m_spriteBatch,
		m_str.c_str(),
		XMFLOAT2(textPos.x-10*m_scaleX, textPos.y-30* m_scaleY),
		XMVectorSet(m_colR, m_colG, m_colB,1),
		0.0,
		XMFLOAT2(0,0),
		XMFLOAT2(m_scaleX,m_scaleY)
	);

	m_spriteBatch->End();
}
