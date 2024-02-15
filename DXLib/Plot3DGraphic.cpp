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
#define AXIS_HEIGHT 100
#define CAM_DIST 100

DX::Plot3DGraphic::Plot3DGraphic(HWND hwnd, int msaa)
	:Graphic(hwnd,msaa)
{
	Actor *tmp;
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
	
	LineMesh* mesh = new LineMesh();
	mesh->Resize(5);
	mesh->SetPos(0, XMFLOAT3(AXIS_WIDTH, 0, 0)) ;
	mesh->SetPos(1, XMFLOAT3(AXIS_WIDTH, 0, AXIS_WIDTH)); ;
	mesh->SetPos(2, XMFLOAT3(AXIS_WIDTH, AXIS_HEIGHT, AXIS_WIDTH));
	mesh->SetPos(3, XMFLOAT3(AXIS_WIDTH, AXIS_HEIGHT, 0)) ;
	mesh->SetPos(4, XMFLOAT3(AXIS_WIDTH, 0, 0)) ;

	mesh->SetColor(0,XMFLOAT4(0,0,0,1));
	mesh->SetColor(1,XMFLOAT4(1,0,0, 1));
	mesh->SetColor(2,XMFLOAT4(0,1,0, 1));
	mesh->SetColor(3,XMFLOAT4(0,0,1, 1));
	mesh->SetColor(4,XMFLOAT4(0,0,0, 1));
	std::vector<int> indiceR = { 0,1,2,3,4 };
	mesh->SetIndice(indiceR.data(), indiceR.size());
	mesh->Update(Device());
	m_axisPX->SetShape(mesh);
	m_axisPX->SetUnlit(true);

	mesh = new LineMesh();
	mesh->Resize(5);
	mesh->SetPos(0,XMFLOAT3(0, 0, 0));
	mesh->SetPos(1,XMFLOAT3(0, 0, AXIS_WIDTH));
	mesh->SetPos(2,XMFLOAT3(0, AXIS_HEIGHT, AXIS_WIDTH));
	mesh->SetPos(3,XMFLOAT3(0, AXIS_HEIGHT, 0));
	mesh->SetPos(4,XMFLOAT3(0, 0, 0));
	mesh->SetColor(0,XMFLOAT4(0, 0, 0,1));
	mesh->SetColor(1,XMFLOAT4(1, 0, 0,1));
	mesh->SetColor(2,XMFLOAT4(0, 1, 0,1));
	mesh->SetColor(3,XMFLOAT4(0, 0, 1,1));
	mesh->SetColor(4,XMFLOAT4(0, 0, 0,1));
	mesh->SetIndice(indiceR.data(), indiceR.size());
	mesh->Update(Device());
	m_axisNX->SetShape(mesh);
	m_axisNX->SetUnlit(true);

	mesh = new LineMesh();
	mesh->Resize(5);
	mesh->SetPos(0, XMFLOAT3(0, 0, AXIS_WIDTH));
	mesh->SetPos(1, XMFLOAT3(0, AXIS_HEIGHT, AXIS_WIDTH));
	mesh->SetPos(2, XMFLOAT3(AXIS_WIDTH, AXIS_HEIGHT, AXIS_WIDTH));
	mesh->SetPos(3, XMFLOAT3(AXIS_WIDTH, 0, AXIS_WIDTH));
	mesh->SetPos(4, XMFLOAT3(0, 0, AXIS_WIDTH));
	mesh->SetColor(0, XMFLOAT4(0, 0, 0,1));
	mesh->SetColor(1, XMFLOAT4(1, 0, 0,1));
	mesh->SetColor(2, XMFLOAT4(0, 1, 0,1));
	mesh->SetColor(3, XMFLOAT4(0, 0, 1,1));
	mesh->SetColor(4, XMFLOAT4(0, 0, 0,1));

	mesh->SetIndice(indiceR.data(), indiceR.size());
	mesh->Update(Device());
	m_axisPZ->SetShape(mesh);
	m_axisPZ->SetUnlit(true);

	mesh = new LineMesh();
	mesh->Resize(5);
	mesh->SetPos(0,XMFLOAT3(0, 0, 0));
	mesh->SetPos(1,XMFLOAT3(0, AXIS_HEIGHT, 0));
	mesh->SetPos(2,XMFLOAT3(AXIS_WIDTH, AXIS_HEIGHT, 0));
	mesh->SetPos(3,XMFLOAT3(AXIS_WIDTH, 0, 0));
	mesh->SetPos(4,XMFLOAT3(0, 0, 0));
	mesh->SetColor(0, XMFLOAT4(0, 0, 0,1));
	mesh->SetColor(1, XMFLOAT4(1, 0, 0,1));
	mesh->SetColor(2, XMFLOAT4(0, 1, 0,1));
	mesh->SetColor(3, XMFLOAT4(0, 0, 1,1));
	mesh->SetColor(4, XMFLOAT4(0, 0, 0,1));
	
	mesh->SetIndice(indiceR.data(), indiceR.size());
	mesh->Update(Device());
	m_axisNZ->SetShape(mesh);
	m_axisNZ->SetUnlit(true);

	mesh = new LineMesh();
	mesh->Resize(5);
	mesh->SetPos(0,XMFLOAT3(0, 0, 0));
	mesh->SetPos(1,XMFLOAT3(AXIS_WIDTH, 0, 0));
	mesh->SetPos(2,XMFLOAT3(AXIS_WIDTH, 0, AXIS_WIDTH));
	mesh->SetPos(3,XMFLOAT3(0, 0, AXIS_WIDTH));
	mesh->SetPos(4,XMFLOAT3(0, 0, 0));
	mesh->SetColor(0,XMFLOAT4(0, 0, 0,1));
	mesh->SetColor(1,XMFLOAT4(1, 0, 0,1));
	mesh->SetColor(2,XMFLOAT4(0, 1, 0,1));
	mesh->SetColor(3,XMFLOAT4(0, 0, 1,1));
	mesh->SetColor(4,XMFLOAT4(0, 0, 0,1));
	mesh->SetIndice(indiceR.data(), indiceR.size());
	mesh->Update(Device());
	m_axisB->SetShape(mesh);
	m_axisB->SetUnlit(true);

	CreateActor(ActorKind::Text, &test);
	((Text*)test)->SetColor(1, 0, 0);
	((Text*)test)->SetPos(100, 100);
	((Text*)test)->SetScale(0.8, 0.8);

}

void DX::Plot3DGraphic::Plot(std::vector<double> x, std::vector<double> y, std::vector<double> z, int r, int g, int b)
{
	assert(x.size() == y.size() && x.size() > 2 && "invalid points");
}

void DX::Plot3DGraphic::Scatter(std::vector<XMFLOAT3> pt, std::vector<float> rads, std::vector<DirectX::XMFLOAT4> colors)
{
	Actor* tmp;
	for (int i = 0; i < pt.size(); ++i)
	{
		CreateActor(ActorKind::Object, &tmp);
		m_scatters.push_back((Object*)tmp);

		m_scatters.back()->SetUnlit(true);
		m_scatters.back()->SetShape(new SphereMesh(Device(), 1));
		m_scatters.back()->GetTransform()->SetScale(rads[i]);
		m_scatters.back()->GetTransform()->SetTranslation(pt[i]);
		auto mesh = m_scatters.back()->GetShape();

		for (int j = 0; j < mesh->Count(); ++j)
		{
			mesh->SetColor(j,colors[i]);
		}
		mesh->Update(Device());
	}
}

void DX::Plot3DGraphic::ClearScatter()
{
	for (auto s : m_scatters)
	{
		s->Release();
	}
	m_scatters.clear();
}

void DX::Plot3DGraphic::ClearPlot()
{
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
	pos = Add({ pos, XMFLOAT3(AXIS_WIDTH / 2, AXIS_HEIGHT / 2, AXIS_WIDTH / 2) });
	
	cam->transform->SetTranslation(pos);
	cam->transform->SetRot(f);


	
}
