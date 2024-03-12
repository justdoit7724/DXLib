#include "pch.h"
#include "Plot3DGraphic.h"
#include "Camera.h"
#include "Transform.h"
#include "Object.h"
#include "LineMesh.h"
#include "SphereMesh.h"

#include "Text.h"
#include <iostream>
using namespace DX;


#define AXIS_WIDTH 100
#define AXIS_HEIGHT 50
#define CAM_DIST 110

DX::Plot3DGraphic::Plot3DGraphic(HWND hwnd, int msaa)
	:Graphic(hwnd,msaa), m_surfaceObj(nullptr), m_axisB(nullptr), m_axisNX(nullptr), m_axisNZ(nullptr),m_axisPX(nullptr),m_axisPZ(nullptr)
{
	Actor* tmp;
	CreateActor(ActorKind::Camera, &tmp);
	SetMainCamera(tmp);

	CreateActor(ActorKind::Object, &tmp);
	m_axisPX = (Object*)tmp;
	CreateActor(ActorKind::Object, &tmp);
	m_axisNX = (Object*)tmp;
	CreateActor(ActorKind::Object, &tmp);
	m_axisPZ = (Object*)tmp;
	CreateActor(ActorKind::Object, &tmp);
	m_axisNZ = (Object*)tmp;
	CreateActor(ActorKind::Object, &tmp);
	m_axisB = (Object*)tmp;
	tmp = nullptr;


	Mesh* mesh = new LineMesh();
	mesh->Resize(11);
	mesh->SetPos(0, XMFLOAT3(0, 0, 0));
	mesh->SetPos(1, XMFLOAT3(0, AXIS_HEIGHT, 0));
	mesh->SetPos(2, XMFLOAT3(AXIS_WIDTH, AXIS_HEIGHT, 0));
	mesh->SetPos(3, XMFLOAT3(AXIS_WIDTH, 0, 0));
	mesh->SetPos(4, XMFLOAT3(0, 0, 0));
	mesh->SetPos(5, XMFLOAT3(AXIS_WIDTH / 4, 0, 0));
	mesh->SetPos(6, XMFLOAT3(AXIS_WIDTH / 4, AXIS_HEIGHT, 0));
	mesh->SetPos(7, XMFLOAT3(2 * AXIS_WIDTH / 4, 0, 0));
	mesh->SetPos(8, XMFLOAT3(2 * AXIS_WIDTH / 4, AXIS_HEIGHT, 0));
	mesh->SetPos(9, XMFLOAT3(3 * AXIS_WIDTH / 4, 0, 0));
	mesh->SetPos(10, XMFLOAT3(3 * AXIS_WIDTH / 4, AXIS_HEIGHT, 0));
	mesh->SetColor(0, COLOR_DARK_GRAY);
	mesh->SetColor(1, COLOR_DARK_GRAY);
	mesh->SetColor(2, COLOR_DARK_GRAY);
	mesh->SetColor(3, COLOR_DARK_GRAY);
	mesh->SetColor(4, COLOR_DARK_GRAY);
	mesh->SetColor(5, COLOR_DARK_GRAY);
	mesh->SetColor(6, COLOR_DARK_GRAY);
	mesh->SetColor(7, COLOR_DARK_GRAY);
	mesh->SetColor(8, COLOR_DARK_GRAY);
	mesh->SetColor(9, COLOR_DARK_GRAY);
	mesh->SetColor(10, COLOR_DARK_GRAY);
	std::vector<int> indiceR = { 0,1, 1,2, 2,3, 3,4,4,0, 5,6,7,8,9,10 };
	mesh->SetIndice(indiceR.data(), indiceR.size());
	m_axisPX->GetTransform()->SetTranslation(AXIS_WIDTH, 0, 0);
	m_axisPX->GetTransform()->SetRot(LEFT);
	m_axisPX->SetShape(mesh);
	m_axisPX->SetUnlit(true);

	m_axisNX->GetTransform()->SetTranslation(0, 0, AXIS_WIDTH);
	m_axisNX->GetTransform()->SetRot(RIGHT);
	m_axisNX->SetShape(new Mesh(mesh));
	m_axisNX->SetUnlit(true);

	m_axisPZ->GetTransform()->SetTranslation(AXIS_WIDTH, 0, AXIS_WIDTH);
	m_axisPZ->GetTransform()->SetRot(BACKWARD);
	m_axisPZ->SetShape(new Mesh(mesh));
	m_axisPZ->SetUnlit(true);

	m_axisNZ->GetTransform()->SetRot(FORWARD);
	m_axisNZ->SetShape(new Mesh(mesh));
	m_axisNZ->SetUnlit(true);

	mesh = new LineMesh();
	mesh->Resize(20);
	mesh->SetPos(0, XMFLOAT3(0, 0, 0));
	mesh->SetPos(1, XMFLOAT3(AXIS_WIDTH, 0, 0));
	mesh->SetPos(2, XMFLOAT3(0, 0, AXIS_WIDTH / 4));
	mesh->SetPos(3, XMFLOAT3(AXIS_WIDTH, 0, AXIS_WIDTH / 4));
	mesh->SetPos(4, XMFLOAT3(0, 0, 2 * AXIS_WIDTH / 4));
	mesh->SetPos(5, XMFLOAT3(AXIS_WIDTH, 0, 2 * AXIS_WIDTH / 4));
	mesh->SetPos(6, XMFLOAT3(0, 0, 3 * AXIS_WIDTH / 4));
	mesh->SetPos(7, XMFLOAT3(AXIS_WIDTH, 0, 3 * AXIS_WIDTH / 4));
	mesh->SetPos(8, XMFLOAT3(0, 0, 4 * AXIS_WIDTH / 4));
	mesh->SetPos(9, XMFLOAT3(AXIS_WIDTH, 0, 4 * AXIS_WIDTH / 4));

	mesh->SetPos(10, XMFLOAT3(0, 0, 0));
	mesh->SetPos(11, XMFLOAT3(0, 0, AXIS_WIDTH));
	mesh->SetPos(12, XMFLOAT3(AXIS_WIDTH / 4, 0, 0));
	mesh->SetPos(13, XMFLOAT3(AXIS_WIDTH / 4, 0, AXIS_WIDTH));
	mesh->SetPos(14, XMFLOAT3(2 * AXIS_WIDTH / 4, 0, 0));
	mesh->SetPos(15, XMFLOAT3(2 * AXIS_WIDTH / 4, 0, AXIS_WIDTH));
	mesh->SetPos(16, XMFLOAT3(3 * AXIS_WIDTH / 4, 0, 0));
	mesh->SetPos(17, XMFLOAT3(3 * AXIS_WIDTH / 4, 0, AXIS_WIDTH));
	mesh->SetPos(18, XMFLOAT3(4 * AXIS_WIDTH / 4, 0, 0));
	mesh->SetPos(19, XMFLOAT3(4 * AXIS_WIDTH / 4, 0, AXIS_WIDTH));
	mesh->SetColor(0, COLOR_DARK_GRAY);
	mesh->SetColor(1, COLOR_DARK_GRAY);
	mesh->SetColor(2, COLOR_DARK_GRAY);
	mesh->SetColor(3, COLOR_DARK_GRAY);
	mesh->SetColor(4, COLOR_DARK_GRAY);
	mesh->SetColor(5, COLOR_DARK_GRAY);
	mesh->SetColor(6, COLOR_DARK_GRAY);
	mesh->SetColor(7, COLOR_DARK_GRAY);
	mesh->SetColor(8, COLOR_DARK_GRAY);
	mesh->SetColor(9, COLOR_DARK_GRAY);
	mesh->SetColor(10, COLOR_DARK_GRAY);
	mesh->SetColor(11, COLOR_DARK_GRAY);
	mesh->SetColor(12, COLOR_DARK_GRAY);
	mesh->SetColor(13, COLOR_DARK_GRAY);
	mesh->SetColor(14, COLOR_DARK_GRAY);
	mesh->SetColor(15, COLOR_DARK_GRAY);
	mesh->SetColor(16, COLOR_DARK_GRAY);
	mesh->SetColor(17, COLOR_DARK_GRAY);
	mesh->SetColor(18, COLOR_DARK_GRAY);
	mesh->SetColor(19, COLOR_DARK_GRAY);
	indiceR.clear();
	for (int i = 0; i < 10; ++i)
	{
		indiceR.push_back(2 * i);
		indiceR.push_back(2 * i + 1);
	}
	mesh->SetIndice(indiceR.data(), indiceR.size());
	m_axisB->SetShape(mesh);
	m_axisB->SetUnlit(true);

	float unitSpacing = AXIS_WIDTH / 35;
	for (int i = 0; i < 5; ++i)
	{
		CreateActor(ActorKind::Text, &tmp);
		m_axisUnitPX.push_back((Text*)tmp);
		m_axisUnitPX.back()->Set3D(true);
		m_axisUnitPX.back()->SetStr(std::to_string(i * AXIS_WIDTH / 4));
		m_axisUnitPX.back()->SetScale(0.5, 0.5);
		m_axisUnitPX.back()->SetPos(AXIS_WIDTH+ unitSpacing, 0, i * AXIS_WIDTH / 4);

		CreateActor(ActorKind::Text, &tmp);
		m_axisUnitNX.push_back((Text*)tmp);
		m_axisUnitNX.back()->Set3D(true);
		m_axisUnitNX.back()->SetStr(std::to_string(i * AXIS_WIDTH / 4));
		m_axisUnitNX.back()->SetScale(0.5, 0.5);
		m_axisUnitNX.back()->SetPos(-unitSpacing, 0, i * AXIS_WIDTH / 4);

		CreateActor(ActorKind::Text, &tmp);
		m_axisUnitPZ.push_back((Text*)tmp);
		m_axisUnitPZ.back()->Set3D(true);
		m_axisUnitPZ.back()->SetStr(std::to_string(i * AXIS_WIDTH / 4));
		m_axisUnitPZ.back()->SetScale(0.5, 0.5);
		m_axisUnitPZ.back()->SetPos(i * AXIS_WIDTH / 4, 0, AXIS_WIDTH + unitSpacing);

		CreateActor(ActorKind::Text, &tmp);
		m_axisUnitNZ.push_back((Text*)tmp);
		m_axisUnitNZ.back()->Set3D(true);
		m_axisUnitNZ.back()->SetStr(std::to_string(i * AXIS_WIDTH / 4));
		m_axisUnitNZ.back()->SetScale(0.5, 0.5);
		m_axisUnitNZ.back()->SetPos(i*AXIS_WIDTH/4, 0, -unitSpacing);
	}
	

	CreateActor(ActorKind::Text, &tmp);
	m_axisTitlePX = (Text*)tmp;
	m_axisTitlePX->Set3D(true);
	m_axisTitlePX->SetStr("X1");
	m_axisTitlePX->SetScale(1.5,1.5);
	m_axisTitlePX->SetPos(AXIS_WIDTH + unitSpacing*4, 0, AXIS_WIDTH / 2);
	CreateActor(ActorKind::Text, &tmp);
	m_axisTitleNX = (Text*)tmp;
	m_axisTitleNX->Set3D(true);
	m_axisTitleNX->SetStr("X1");
	m_axisTitleNX->SetScale(1.5, 1.5);
	m_axisTitleNX->SetPos(- unitSpacing * 4, 0, AXIS_WIDTH / 2);
	CreateActor(ActorKind::Text, &tmp);
	m_axisTitlePZ = (Text*)tmp;
	m_axisTitlePZ->Set3D(true);
	m_axisTitlePZ->SetStr("X2");
	m_axisTitlePZ->SetScale(1.5, 1.5);
	m_axisTitlePZ->SetPos(AXIS_WIDTH / 2, 0, AXIS_WIDTH+  unitSpacing * 4);
	CreateActor(ActorKind::Text, &tmp);
	m_axisTitleNZ = (Text*)tmp;
	m_axisTitleNZ->Set3D(true);
	m_axisTitleNZ->SetStr("X2");
	m_axisTitleNZ->SetScale(1.5, 1.5);
	m_axisTitleNZ->SetPos(AXIS_WIDTH / 2, 0, 0 - unitSpacing * 4);

}

DX::Plot3DGraphic::~Plot3DGraphic()
{
	Clear();
}

void DX::Plot3DGraphic::Update(float spf)
{
	auto mainCam = (Camera*)MainCamera();
	bool enablePX = Dot(mainCam->transform->GetForward(), m_axisPX->GetTransform()->GetForward()) < 0.4;
	bool enableNX = Dot(mainCam->transform->GetForward(), m_axisNX->GetTransform()->GetForward()) < 0.4;
	bool enablePZ = Dot(mainCam->transform->GetForward(), m_axisPZ->GetTransform()->GetForward()) < 0.4;
	bool enableNZ = Dot(mainCam->transform->GetForward(), m_axisNZ->GetTransform()->GetForward()) < 0.4;
	for (int i = 0; i < 5; ++i)
	{
		m_axisUnitPX[i]->SetEnable(!enablePX);
		m_axisUnitNX[i]->SetEnable(!enableNX);
		m_axisUnitPZ[i]->SetEnable(!enablePZ);
		m_axisUnitNZ[i]->SetEnable(!enableNZ);
	}
	m_axisPX->SetEnable(enablePX);
	m_axisNX->SetEnable(enableNX);
	m_axisPZ->SetEnable(enablePZ);
	m_axisNZ->SetEnable(enableNZ);
	m_axisTitlePX->SetEnable(!enablePX);
	m_axisTitleNX->SetEnable(!enableNX);
	m_axisTitlePZ->SetEnable(!enablePZ);
	m_axisTitleNZ->SetEnable(!enableNZ);

	Graphic::Update(spf);
}

void DX::Plot3DGraphic::Plot(std::vector<DirectX::XMFLOAT3> pt, DirectX::XMFLOAT4 color)
{
	assert(pt.size() >= 2 && "invalid points");

	m_linesPos.push_back(pt);
	m_linesCol.push_back(color);

	UpdatePlot();
}

void DX::Plot3DGraphic::Scatter(std::vector<XMFLOAT3> pt, std::vector<float> rads, std::vector<DirectX::XMFLOAT4> colors)
{
	m_scattersPt.push_back(pt);
	m_scattersRad.push_back(rads);
	m_scattersCol.push_back(colors);

	UpdatePlot();
}

void DX::Plot3DGraphic::Surface(std::vector<std::vector<float>> x1, std::vector<std::vector<float>> x2, std::vector<std::vector<float>> v, float colRangeBegin, float colRangeEnd)
{
	m_surfaceX1 = x1;
	m_surfaceX2 = x2;
	m_surfaceV = v;
	m_surfaceColRange = { colRangeBegin, colRangeEnd };

	UpdatePlot();
}

void DX::Plot3DGraphic::ClearSurface()
{
	m_surfaceX1.clear();
	m_surfaceX2.clear();
	m_surfaceV.clear();
}

void DX::Plot3DGraphic::ClearLines()
{
	m_linesCol.clear();
	m_linesPos.clear();
	if (m_linesObj.size())
	{
		for (auto o : m_linesObj)
		{
			o->Release();
		}
		m_linesObj.clear();
	}
}

void DX::Plot3DGraphic::ClearAxis()
{
	if (m_axisB)
	{
		m_axisB->Release();
		m_axisB = nullptr;
		m_axisNX->Release();
		m_axisNX = nullptr;
		m_axisNZ->Release();
		m_axisNZ = nullptr;
		m_axisPX->Release();
		m_axisPX = nullptr;
		m_axisPZ->Release();
		m_axisPZ = nullptr;
	}
}

void DX::Plot3DGraphic::ClearScatters()
{
	m_scattersCol.clear();
	m_scattersPt.clear();
	m_scattersRad.clear();

	if (m_scattersObj.size())
	{
		for (auto o : m_scattersObj)
		{
			o->Release();
		}
		m_scattersObj.clear();
	}
}

void DX::Plot3DGraphic::Clear()
{
	ClearScatters();

	ClearSurface();
	ClearLines();

	ClearAxis();
}

void DX::Plot3DGraphic::SetX1Title(std::string title)
{
	m_axisTitleNZ->SetStr(title);
	m_axisTitlePZ->SetStr(title);
}

void DX::Plot3DGraphic::SetX2Title(std::string title)
{
	m_axisTitleNX->SetStr(title);
	m_axisTitlePX->SetStr(title);
}




void DX::Plot3DGraphic::UpdateCamMovement(float spf)
{
	if (!m_mainCamera || !m_enableCamMovement)
	{
		return;
	}

	auto cam = (Camera*)m_mainCamera;
	const float speed = 50;


	static float angleVer = 0;
	static float angleHor = 0;
	static XMFLOAT2 prevMousePt(0,0);
	const float angleSpeed = 3.141592f * 0.15f;
	if (m_mouseRClicked)
	{
		angleHor += angleSpeed * spf * (m_mouseX - prevMousePt.x);
		angleVer += angleSpeed * spf * (m_mouseY - prevMousePt.y);
		angleVer = Clamp(-PI*0.49, PI * 0.49, angleVer);
	}
	prevMousePt.x = m_mouseX;
	prevMousePt.y = m_mouseY;
	XMFLOAT3 pos(0, 0, -CAM_DIST);
	XMMATRIX rotMat = XMMatrixRotationX(angleVer) * XMMatrixRotationY(angleHor);
	pos = Multiply(pos, rotMat);
	XMFLOAT3 f = Normalize(Neg(pos));
	pos = pos+ XMFLOAT3(AXIS_WIDTH / 2, AXIS_HEIGHT / 2, AXIS_WIDTH / 2);
	
	cam->transform->SetTranslation(pos);
	cam->transform->SetRot(f);


	
}

void DX::Plot3DGraphic::UpdatePlot()
{
	for (auto o : m_linesObj)
	{
		o->Release();
	}
	m_linesObj.clear();
	for (auto o : m_scattersObj)
	{
		o->Release();
	}
	m_scattersObj.clear();
	if (m_surfaceObj)
	{
		m_surfaceObj->Release();
		m_surfaceObj = nullptr;
	}

	//calculate range
	XMFLOAT2 x1Range(FLT_MAX, FLT_MIN);
	XMFLOAT2 x2Range(FLT_MAX, FLT_MIN);
	XMFLOAT2 vRange(FLT_MAX, FLT_MIN);
	float x1Length;
	float x2Length;
	float vLength;
	{
		for (int i = 0; i < m_scattersPt.size(); ++i)
		{
			for (int j = 0; j < m_scattersPt[i].size(); ++j)
			{
				x1Range.x = min(x1Range.x, m_scattersPt[i][j].x);
				x1Range.y = max(x1Range.y, m_scattersPt[i][j].x);
				x2Range.x = min(x2Range.x, m_scattersPt[i][j].y);
				x2Range.y = max(x2Range.y, m_scattersPt[i][j].y);
				vRange.x = min(vRange.x, m_scattersPt[i][j].z);
				vRange.y = max(vRange.y, m_scattersPt[i][j].z);
			}
		}

		for (int y = 0; y < m_surfaceX1.size(); ++y)
		{
			for (int x = 0; x < m_surfaceX1[y].size(); ++x)
			{
				x1Range.x = min(x1Range.x, m_surfaceX1[y][x]);
				x1Range.y = max(x1Range.y, m_surfaceX1[y][x]);
				x2Range.x = min(x2Range.x, m_surfaceX2[y][x]);
				x2Range.y = max(x2Range.y, m_surfaceX2[y][x]);
				vRange.x = min(vRange.x, m_surfaceV[y][x]);
				vRange.y = max(vRange.y, m_surfaceV[y][x]);
			}
		}
		x1Length = x1Range.y - x1Range.x;
		x2Length = x2Range.y - x2Range.x;
		vLength = vRange.y - vRange.x;
	}

	//Create & Update Scatter Obj
	if(m_scattersPt.size())
	{
		for (int i = 0; i < m_scattersPt.size(); ++i)
		{
			for (int j = 0; j < m_scattersPt[i].size(); ++j)
			{
				XMFLOAT3 mPt;
				mPt.x = (m_scattersPt[i][j].x - x1Range.x) / x1Length;
				mPt.y = (m_scattersPt[i][j].y - x2Range.x) / x2Length;
				mPt.z = (m_scattersPt[i][j].z - vRange.x) / vLength;

				Actor* tmp;
				CreateActor(ActorKind::Object, &tmp);
				m_scattersObj.push_back((Object*)tmp);

				m_scattersObj.back()->SetUnlit(true);
				m_scattersObj.back()->SetShape(new SphereMesh(Device(), 1));
				m_scattersObj.back()->GetTransform()->SetScale(m_scattersRad[i][j]);
				m_scattersObj.back()->GetTransform()->SetTranslation(mPt);
				auto mesh = m_scattersObj.back()->GetShape();

				for (int k = 0; k < mesh->Count(); ++k)
				{
					mesh->SetColor(k, m_scattersCol[i][j]);
				}
			}
		}
	}
	

	//Create & Update Surface
	if(m_surfaceX1.size())
	{
		const int n1 = m_surfaceX1[0].size();
		const int n2 = m_surfaceX1.size();

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
				vert.pos.x = AXIS_WIDTH * (m_surfaceX1[j][i] - x1Range.x) / (x1Range.y - x1Range.x);
				vert.pos.z = AXIS_WIDTH * (m_surfaceX2[j][i] - x2Range.x) / (x2Range.y - x2Range.x);
				vert.pos.y = AXIS_HEIGHT * (m_surfaceV[j][i] - vRange.x) / (vRange.y - vRange.x);

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

	//Update Axis Unit
	for (int i = 0; i < 5; ++i)
	{
		m_axisUnitPX[i]->SetStr(ToString(x2Range.x + x2Length * i, 0));

		m_axisUnitNX[i]->SetStr(ToString(x2Range.x + x2Length * i,0));

		m_axisUnitPZ[i]->SetStr(ToString(x1Range.x + x1Length * i,0));

		m_axisUnitNZ[i]->SetStr(ToString(x1Range.x + x1Length*i,0));
	}
}
