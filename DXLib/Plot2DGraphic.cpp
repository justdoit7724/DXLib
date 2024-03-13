#include "pch.h"
#include "Plot2DGraphic.h"
#include "Object.h"
#include "LineMesh.h"
#include "Transform.h"
#include "Text.h"
#include "CircleMesh.h"
#include "Camera.h"

using namespace DX;

#define SCN_PLOT_MARGIN_LEFT 50
#define SCN_PLOT_MARGIN_BOTTOM 50
#define SCN_PLOT_WIDTH 400
#define SCN_PLOT_HEIGHT 400

#define PLOT_RES_WIDTH 500
#define PLOT_RES_HEIGHT 500

Plot2DGraphic::Plot2DGraphic(HWND hwnd)
	:Graphic(hwnd), m_axis(nullptr), m_surfaceObj(nullptr)
{
	auto rc = GetWndSize();
	const int width = rc.right - rc.left;
	const int height = rc.bottom - rc.top;


	Actor* tmp;
	CreateActor(ActorKind::Camera, &tmp);
	auto cam = (Camera*)tmp;
	cam->SetFrame(FRAME_KIND_ORTHOGONAL, XMFLOAT2(width, height), 0.1, 100, NULL, NULL);
	cam->transform->SetRot(FORWARD);
	SetMainCamera(cam);
	cam->transform->SetTranslation((SCN_PLOT_MARGIN_LEFT + SCN_PLOT_WIDTH)/2, (SCN_PLOT_MARGIN_BOTTOM + SCN_PLOT_HEIGHT) / 2, -10);

	CreateActor(ActorKind::Object, &tmp);
	m_axis = (Object*)tmp;
	tmp = nullptr;


	Mesh* mesh = new LineMesh();
	mesh->Resize(3);
	mesh->SetPos(0, XMFLOAT3(SCN_PLOT_MARGIN_LEFT, SCN_PLOT_MARGIN_BOTTOM, 0));
	mesh->SetPos(1, XMFLOAT3(SCN_PLOT_MARGIN_LEFT+ SCN_PLOT_WIDTH, SCN_PLOT_MARGIN_BOTTOM, 0));
	mesh->SetPos(2, XMFLOAT3(SCN_PLOT_MARGIN_LEFT, SCN_PLOT_MARGIN_BOTTOM + SCN_PLOT_HEIGHT,0));
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
		m_axisHorUnits.back()->SetPos(SCN_PLOT_MARGIN_LEFT+i* SCN_PLOT_WIDTH /6, SCN_PLOT_MARGIN_BOTTOM - unitSpacing, 0);

		CreateActor(ActorKind::Text, &tmp);
		m_axisVerUnits.push_back((Text*)tmp);
		m_axisVerUnits.back()->Set3D(true);
		std::string str = std::to_string(i * SCN_PLOT_HEIGHT / 6);
		m_axisVerUnits.back()->SetStr(str);
		m_axisVerUnits.back()->SetScale(0.5, 0.5);
		m_axisVerUnits.back()->SetPos(SCN_PLOT_MARGIN_LEFT - unitSpacing * str.size(), SCN_PLOT_MARGIN_BOTTOM + i * SCN_PLOT_HEIGHT / 6, 0);

	}


	//CreateActor(ActorKind::Object, &tmp);
	//m_plotQuad = (Object*)tmp;
	//m_plotQuad->GetTransform()->SetTranslation(0, 0, 0);
	//m_plotQuad->SetUnlit(true);
	//mesh=m_plotQuad->GetShape();
	//mesh->Clear();
	//mesh->Resize(4);
	//Vertex vertex;
	//vertex.pos = { SCN_PLOT_MARGIN_LEFT, 0, SCN_PLOT_MARGIN_BOTTOM };
	//vertex.tex = { 0,1 };
	//vertex.color = COLOR_RED;
	//mesh->SetVertex(0, vertex);
	//vertex.pos = { SCN_PLOT_MARGIN_LEFT+ SCN_PLOT_WIDTH, 0, SCN_PLOT_MARGIN_BOTTOM };
	//vertex.tex = { 1,1 };
	//vertex.color = COLOR_BLUE;
	//mesh->SetVertex(1, vertex);
	//vertex.pos = { SCN_PLOT_MARGIN_LEFT, 0, SCN_PLOT_MARGIN_BOTTOM+ SCN_PLOT_HEIGHT };
	//vertex.tex = { 0,0 };
	//vertex.color = COLOR_GREEN;
	//mesh->SetVertex(2, vertex);
	//vertex.pos = { SCN_PLOT_MARGIN_LEFT + SCN_PLOT_WIDTH, 0, SCN_PLOT_MARGIN_BOTTOM + SCN_PLOT_HEIGHT };
	//vertex.tex = { 1,0 };
	//vertex.color = COLOR_DARK_GRAY;
	//mesh->SetVertex(3, vertex);

	//indice.clear();
	//indice.push_back(0);
	//indice.push_back(2);
	//indice.push_back(1);
	//indice.push_back(1);
	//indice.push_back(2);
	//indice.push_back(3);
	//mesh->SetIndice(indice.data(), indice.size());




}

DX::Plot2DGraphic::~Plot2DGraphic()
{
	Clear();
}

void DX::Plot2DGraphic::Update(float spf)
{
	Graphic::Update(spf);
}

void DX::Plot2DGraphic::Plot(std::vector<DirectX::XMFLOAT2> pt, DirectX::XMFLOAT4 color, float thick)
{
	m_linesPos.push_back(pt);
	m_linesCol.push_back(color);
	m_linesThick.push_back(thick);

	UpdatePlot();
}

void DX::Plot2DGraphic::Scatter(std::vector<DirectX::XMFLOAT2> pt, std::vector<float> rads, std::vector<DirectX::XMFLOAT4> colors)
{
	m_scatterPts.push_back(pt);
	m_scatterRads.push_back(rads);
	m_scatterCols.push_back(colors);

	UpdatePlot();
}

void DX::Plot2DGraphic::Surface(std::vector<std::vector<float>> x, std::vector<std::vector<float>> y, std::vector<std::vector<float>> v, float colRangeBegin, float colRangeEnd)
{

	m_surfaceX = x;
	m_surfaceY = y;
	m_surfaceV = v;
	m_surfaceColRange = { colRangeBegin, colRangeEnd };

	UpdatePlot();
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
	m_scatterCols.clear();
	m_scatterPts.clear();
	m_scatterRads.clear();
	for (auto o : m_scatterObjs)
	{
		o->Release();
	}
	m_scatterObjs.clear();
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

void DX::Plot2DGraphic::UpdatePlot()
{
	for (auto o : m_scatterObjs)
	{
		o->Release();
	}
	m_scatterObjs.clear();
	for (auto l : m_linesObj)
	{
		l->Release();
	}
	m_linesObj.clear();
	if (m_surfaceObj)
	{
		m_surfaceObj->Release();
		m_surfaceObj = nullptr;
	}

	//calculate range
	XMFLOAT2 x1Range(FLT_MAX, FLT_MIN);
	XMFLOAT2 x2Range(FLT_MAX, FLT_MIN);
	float x1Length;
	float x2Length;
	{
		for (int i = 0; i < m_scatterPts.size(); ++i)
		{
			for (int j = 0; j < m_scatterPts[i].size(); ++j)
			{
				x1Range.x = min(x1Range.x, m_scatterPts[i][j].x);
				x1Range.y = max(x1Range.y, m_scatterPts[i][j].x);
				x2Range.x = min(x2Range.x, m_scatterPts[i][j].y);
				x2Range.y = max(x2Range.y, m_scatterPts[i][j].y);
			}
		}

		for (int y = 0; y < m_linesPos.size(); ++y)
		{
			for (int x = 0; x < m_linesPos[y].size(); ++x)
			{
				x1Range.x = min(x1Range.x, m_linesPos[y][x].x);
				x1Range.y = max(x1Range.y, m_linesPos[y][x].x);
				x2Range.x = min(x2Range.x, m_linesPos[y][x].y);
				x2Range.y = max(x2Range.y, m_linesPos[y][x].y);
			}
		}


		for (int y = 0; y < m_surfaceX.size(); ++y)
		{
			for (int x = 0; x < m_surfaceX[y].size(); ++x)
			{
				x1Range.x = min(x1Range.x, m_surfaceX[y][x]);
				x1Range.y = max(x1Range.y, m_surfaceX[y][x]);
				x2Range.x = min(x2Range.x, m_surfaceY[y][x]);
				x2Range.y = max(x2Range.y, m_surfaceY[y][x]);
			}
		}

		x1Length = x1Range.y - x1Range.x;
		x2Length = x2Range.y - x2Range.x;
	}


	//Create & Update Scatter Obj
	for (int i = 0; i < m_scatterPts.size(); ++i)
	{
		for (int j = 0; j < m_scatterPts[i].size(); ++j)
		{
			XMFLOAT3 mPt;
			mPt.x = ((m_scatterPts[i][j].x - x1Range.x) / x1Length)*SCN_PLOT_WIDTH + SCN_PLOT_MARGIN_LEFT;
			mPt.y = ((m_scatterPts[i][j].y - x2Range.x) / x2Length)*SCN_PLOT_HEIGHT + SCN_PLOT_MARGIN_BOTTOM;
			mPt.z = -0.02;

			Actor* tmp;
			CreateActor(ActorKind::Object, &tmp);
			m_scatterObjs.push_back((Object*)tmp);

			m_scatterObjs.back()->SetUnlit(true);
			m_scatterObjs.back()->SetShape(new CircleMesh(Device(), 10));
			m_scatterObjs.back()->GetTransform()->SetScale(m_scatterRads[i][j]);
			m_scatterObjs.back()->GetTransform()->SetTranslation(mPt);
			m_scatterObjs.back()->GetTransform()->SetRot(UP);
			auto mesh = m_scatterObjs.back()->GetShape();

			for (int k = 0; k < mesh->Count(); ++k)
			{
				mesh->SetColor(k, m_scatterCols[i][j]);
			}
		}
	}


	//Create & Update Line Obj
	std::vector<int> indice;
	indice.push_back(0);
	indice.push_back(1);
	indice.push_back(2);
	indice.push_back(1);
	indice.push_back(3);
	indice.push_back(2);
	for (int i = 0; i < m_linesPos.size(); i++)
	{
		for (int j = 0; j < m_linesPos[i].size() - 1; j += 2)
		{
			XMFLOAT3 mPt1;
			mPt1.x = ((m_linesPos[i][j].x - x1Range.x) / x1Length)*SCN_PLOT_WIDTH + SCN_PLOT_MARGIN_LEFT;
			mPt1.y = ((m_linesPos[i][j].y - x2Range.x) / x2Length)*SCN_PLOT_HEIGHT+SCN_PLOT_MARGIN_BOTTOM;
			mPt1.z = -0.01;
			XMFLOAT3 mPt2;
			mPt2.x = ((m_linesPos[i][j+1].x - x1Range.x) / x1Length)*SCN_PLOT_WIDTH+SCN_PLOT_MARGIN_LEFT;
			mPt2.y = ((m_linesPos[i][j+1].y - x2Range.x) / x2Length)*SCN_PLOT_HEIGHT+SCN_PLOT_MARGIN_BOTTOM;
			mPt2.z = -0.01;

			XMFLOAT3 dir = Normalize(mPt1 - mPt2);
			XMFLOAT3 sideDir = Cross(dir, BACKWARD);

			Actor* tmp;
			CreateActor(ActorKind::Object, &tmp);
			m_linesObj.push_back((Object*)tmp);
			m_linesObj.back()->SetUnlit(true);
			auto mesh = m_linesObj.back()->GetShape();
			mesh->Clear();
			mesh->Resize(4);
			mesh->SetPos(0, mPt1 + sideDir * (m_linesThick[i] / 2));
			mesh->SetPos(1, mPt1 - sideDir * (m_linesThick[i] / 2));
			mesh->SetPos(2, mPt2 + sideDir * (m_linesThick[i] / 2));
			mesh->SetPos(3, mPt2 - sideDir * (m_linesThick[i] / 2));

			for (int k = 0; k < mesh->Count(); ++k)
			{
				mesh->SetColor(k, m_linesCol[i]);
			}
			mesh->SetIndice(indice.data(), indice.size());
		}
	}

	//Create & Update Surface
	if (m_surfaceX.size())
	{
		const int n1 = m_surfaceX[0].size();
		const int n2 = m_surfaceX.size();

		Actor* tmp;
		CreateActor(ActorKind::Object, &tmp);
		m_surfaceObj = (Object*)tmp;
		m_surfaceObj->SetUnlit(true);
		auto mesh = m_surfaceObj->GetShape();
		mesh->Clear();
		mesh->Resize(n1 * n2);
		for (int j = 0; j < n2; ++j)
		{
			for (int i = 0; i < n1; ++i)
			{
				int index = j * n1 + i;

				Vertex vert;
				vert.pos.x = SCN_PLOT_WIDTH * (m_surfaceX[j][i] - x1Range.x) / x1Length + SCN_PLOT_MARGIN_LEFT;
				vert.pos.y = SCN_PLOT_HEIGHT * (m_surfaceY[j][i] - x2Range.x) / x2Length+ SCN_PLOT_MARGIN_BOTTOM;
				vert.pos.z = 0;

				auto col = GetColorScale((m_surfaceV[j][i] - m_surfaceColRange.x) / (m_surfaceColRange.y - m_surfaceColRange.x));
				vert.color.x = col.x;
				vert.color.y = col.y;
				vert.color.z = col.z;
				vert.color.w = 1;
				mesh->SetVertex(index, vert);
			}
		}

		std::vector<int> indice;
		for (int y = 0; y < n2 - 1; ++y)
		{
			for (int x = 0; x < n1 - 1; ++x)
			{
				int bl = y * n1 + x;
				int br = bl + 1;
				int tl = bl + n1;
				int tr = bl + 1 + n1;

				indice.push_back(bl);
				indice.push_back(tl);
				indice.push_back(br);
				indice.push_back(br);
				indice.push_back(tl);
				indice.push_back(tr);
			}
		}
		mesh->SetIndice(indice.data(), indice.size());
	}


	//Update axis
	for (int i = 0; i < m_axisVerUnits.size(); ++i)
	{
		m_axisHorUnits[i]->SetStr(ToString(x1Range.x + x1Length * i, 0));

		m_axisVerUnits[i]->SetStr(ToString(x2Range.x + x2Length * i, 0));
	}
}
