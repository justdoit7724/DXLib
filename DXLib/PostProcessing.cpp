#include "pch.h"
#include "PostProcessing.h"
#include "Shader.h"
#include "Mesh.h"
#include "ShaderFormat.h"
#include "BlendState.h";
#include "Graphic.h"

using namespace DX;

PostProcessing::PostProcessing(ID3D11Device* device, std::string psPath)
{
	/*
	auto stdDescs = D3DLayout_Std().GetLayout();

	m_vs = new VShader(device, "HL_PP_StdVS.cso", stdDescs.data(), stdDescs.size());
	m_ps = new PShader(device, psPath);
	*/

}

PostProcessing::~PostProcessing()
{
}

void PostProcessing::Render(const Graphic* graphic, ID3D11RenderTargetView* rtv)
{
	if (!rtv)
	{
		graphic->DContext()->OMGetRenderTargets(1, &rtv, nullptr);
	}

	ID3D11RenderTargetView* dxRTVTmp;
	ID3D11DepthStencilView* dxDSTemp;
	graphic->DContext()->OMGetRenderTargets(1, &dxRTVTmp, &dxDSTemp);

	graphic->DContext()->OMSetRenderTargets(1, &rtv, nullptr);

	m_vs->Apply(graphic);
	m_ps->Apply(graphic);
	m_screenMesh->Apply(graphic);

	graphic->DContext()->OMSetRenderTargets(1, &dxRTVTmp, dxDSTemp);
}
