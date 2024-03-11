#include "pch.h"
#include "Plot2DGraphic.h"
#include "Object.h"
#include "LineMesh.h"
#include "Transform.h"
#include "Text.h"
#include "Camera.h"

using namespace DX;

#define SCN_PLOT_MARGIN_LEFT 50
#define SCN_PLOT_MARGIN_BOTTOM 50
#define SCN_PLOT_WIDTH 400
#define SCN_PLOT_HEIGHT 400

Plot2DGraphic::Plot2DGraphic(HWND hwnd)
	:Graphic(hwnd), m_axis(nullptr)
{
	Actor* tmp;
	CreateActor(ActorKind::Camera, &tmp);
	auto cam = (Camera*)tmp;
	auto rc = GetWndSize();
	cam->SetFrame(FRAME_KIND_ORTHOGONAL, XMFLOAT2( rc.right - rc.left , rc.bottom - rc.top ), 0.1, 100, NULL, NULL);
	cam->transform->SetRot(DOWN, FORWARD);
	SetMainCamera(cam);
	cam->transform->SetTranslation((SCN_PLOT_MARGIN_LEFT + SCN_PLOT_WIDTH)/2, 10, (SCN_PLOT_MARGIN_BOTTOM + SCN_PLOT_HEIGHT)/2);

	CreateActor(ActorKind::Object, &tmp);
	m_axis = (Object*)tmp;
	tmp = nullptr;


	Mesh* mesh = new LineMesh();
	mesh->Resize(3);
	mesh->SetPos(0, XMFLOAT3(SCN_PLOT_MARGIN_LEFT, 0, SCN_PLOT_MARGIN_BOTTOM));
	mesh->SetPos(1, XMFLOAT3(SCN_PLOT_MARGIN_LEFT+ SCN_PLOT_WIDTH, 0, SCN_PLOT_MARGIN_BOTTOM));
	mesh->SetPos(2, XMFLOAT3(SCN_PLOT_MARGIN_LEFT, 0, SCN_PLOT_MARGIN_BOTTOM+ SCN_PLOT_HEIGHT));
	mesh->SetColor(0, COLOR_DARK_GRAY);
	mesh->SetColor(1, COLOR_DARK_GRAY);
	mesh->SetColor(2, COLOR_DARK_GRAY);
	std::vector<int> indice = { 0,1, 0,2 };
	mesh->SetIndice(indice.data(), indice.size());
	m_axis->GetTransform()->SetTranslation(0, 0, 0);
	m_axis->SetShape(mesh);
	m_axis->SetUnlit(true);


	float unitSpacing = 10;
	for (int i = 0; i < 7; ++i)
	{
		CreateActor(ActorKind::Text, &tmp);
		m_axisHorUnits.push_back((Text*)tmp);
		m_axisHorUnits.back()->Set3D(true);
		m_axisHorUnits.back()->SetStr(std::to_string(i * SCN_PLOT_WIDTH / 6));
		m_axisHorUnits.back()->SetScale(0.5, 0.5);
		m_axisHorUnits.back()->SetPos(SCN_PLOT_MARGIN_LEFT+i* SCN_PLOT_WIDTH /6, 0, SCN_PLOT_MARGIN_BOTTOM -unitSpacing);

		CreateActor(ActorKind::Text, &tmp);
		m_axisVerUnits.push_back((Text*)tmp);
		m_axisVerUnits.back()->Set3D(true);
		std::string str = std::to_string(i * SCN_PLOT_HEIGHT / 6);
		m_axisVerUnits.back()->SetStr(str);
		m_axisVerUnits.back()->SetScale(0.5, 0.5);
		m_axisVerUnits.back()->SetPos(SCN_PLOT_MARGIN_LEFT - unitSpacing * str.size(), 0, SCN_PLOT_MARGIN_BOTTOM + i * SCN_PLOT_HEIGHT / 6);

	}


	CreateActor(ActorKind::Object, &tmp);
	m_plotQuad = (Object*)tmp;
	m_plotQuad->GetTransform()->SetTranslation(0, 0, 0);
	m_plotQuad->SetUnlit(true);
	mesh=m_plotQuad->GetShape();
	mesh->Clear();
	mesh->Resize(4);
	Vertex vertex;
	vertex.pos = { SCN_PLOT_MARGIN_LEFT, 0, SCN_PLOT_MARGIN_BOTTOM };
	vertex.tex = { 0,1 };
	vertex.color = COLOR_RED;
	mesh->SetVertex(0, vertex);
	vertex.pos = { SCN_PLOT_MARGIN_LEFT+ SCN_PLOT_WIDTH, 0, SCN_PLOT_MARGIN_BOTTOM };
	vertex.tex = { 1,1 };
	vertex.color = COLOR_BLUE;
	mesh->SetVertex(1, vertex);
	vertex.pos = { SCN_PLOT_MARGIN_LEFT, 0, SCN_PLOT_MARGIN_BOTTOM+ SCN_PLOT_HEIGHT };
	vertex.tex = { 0,0 };
	vertex.color = COLOR_GREEN;
	mesh->SetVertex(2, vertex);
	vertex.pos = { SCN_PLOT_MARGIN_LEFT + SCN_PLOT_WIDTH, 0, SCN_PLOT_MARGIN_BOTTOM + SCN_PLOT_HEIGHT };
	vertex.tex = { 1,0 };
	vertex.color = COLOR_DARK_GRAY;
	mesh->SetVertex(3, vertex);

	indice.clear();
	indice.push_back(0);
	indice.push_back(2);
	indice.push_back(1);
	indice.push_back(1);
	indice.push_back(2);
	indice.push_back(3);
	mesh->SetIndice(indice.data(), indice.size());
}

DX::Plot2DGraphic::~Plot2DGraphic()
{
	Clear();
}

void DX::Plot2DGraphic::Plot(std::vector<DirectX::XMFLOAT2> pt, DirectX::XMFLOAT3 color)
{
}

void DX::Plot2DGraphic::Scatter(std::vector<DirectX::XMFLOAT2> pt, std::vector<float> rads, std::vector<DirectX::XMFLOAT3> colors)
{
}

void DX::Plot2DGraphic::Clear()
{
	ClearPlot();
	ClearScatter();
	ClearAxis();
}

void DX::Plot2DGraphic::ClearPlot()
{
}

void DX::Plot2DGraphic::ClearScatter()
{
}

void DX::Plot2DGraphic::ClearAxis()
{
	for (int i = 0; i < m_axisHorUnits.size(); ++i)
	{
		m_axisHorUnits[i]->Release();
		m_axisVerUnits[i]->Release();
	}
	m_axisHorUnits.clear();
	m_axisVerUnits.clear();

	m_axis->Release();
	m_axis = nullptr;
}

void DX::Plot2DGraphic::UpdateCamMovement(float spf)
{
}
