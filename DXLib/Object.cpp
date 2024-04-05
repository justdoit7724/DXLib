
#include "pch.h"

#include "Object.h"
#include "ShaderFormat.h"
#include "Camera.h"
#include "ShaderReg.h"
#include "Transform.h"
#include "Shader.h"
#include "BlendState.h"
#include "DepthStencilState.h"
#include "RasterizerState.h"
#include "Mesh.h"
#include "LayerMask.h"
#include "Collider.h"
#include "Graphic.h"

using namespace DX;

//fundamental elements
/*
Object::Object(ID3D11Device* device, ID3D11DeviceContext* dContext, std::string name, std::shared_ptr <Mesh> mesh, std::shared_ptr<Collider> collider, std::string sVS, const D3D11_INPUT_ELEMENT_DESC* iLayouts, UINT layoutCount, std::string sHS, std::string sDS, std::string sGS, std::string sPS, bool bDirectRender)
	:name(name), m_mesh(mesh), m_collider(collider), layer(LAYER_STD)
{
	transform = new Transform();
	vs = new VShader(device,sVS, iLayouts, layoutCount);
	hs = new HShader(device,sHS);
	ds = new DShader(device,sDS);
	gs = new GShader(device,sGS);
	ps = new PShader(device,sPS);

	blendState = new BlendState(device,nullptr);
	dsState = new DepthStencilState(device, nullptr);
	rsState = new RasterizerState(device,nullptr);

	m_material = new SHADER_MATERIAL(XMFLOAT3(0.6, 0.6, 0.6), 0.4, XMFLOAT3(0.6, 0.6, 0.6), XMFLOAT3(1.0, 1.0, 1.0));
}

//standard elements
Object::Object(ID3D11Device* device, ID3D11DeviceContext* dContext, std::string name, std::shared_ptr <Mesh> mesh, std::shared_ptr<Collider> collider, ID3D11ShaderResourceView* diffSRV, ID3D11ShaderResourceView* normalSRV, bool directRender)
	: name(name), m_mesh(mesh), m_collider(collider), layer(LAYER_STD), m_mainTex(diffSRV), m_normal(normalSRV)
{
	auto stdDescs = D3DLayout_Std().GetLayout();

	transform = new Transform();
	vs = new VShader(device,"StdVS.cso", stdDescs.data(), stdDescs.size());
	hs = new HShader(device);
	ds = new DShader(device);
	gs = new GShader(device);
	ps = new PShader(device,"StdPS.cso");

	m_material = new SHADER_MATERIAL(XMFLOAT3(0.6, 0.6, 0.6), 0.4, XMFLOAT3(0.6, 0.6, 0.6), XMFLOAT3(1.0, 1.0, 1.0));

	vs->AddCB(device, 0, 1, sizeof(SHADER_STD_TRANSF));
	ps->AddCB(device, SHADER_REG_CB_MATERIAL, 1, sizeof(SHADER_MATERIAL));
	ps->WriteCB(dContext, SHADER_REG_CB_MATERIAL,m_material);
	
	ps->AddSRV(SHADER_REG_SRV_DIFFUSE, 1);
	ps->AddSRV(SHADER_REG_SRV_NORMAL, 1);
	ps->WriteSRV(SHADER_REG_SRV_DIFFUSE, m_mainTex);
	ps->WriteSRV(SHADER_REG_SRV_NORMAL, m_normal);

	blendState = new BlendState(device, nullptr);
	dsState = new DepthStencilState(device, nullptr);
	rsState = new RasterizerState(device, nullptr);

}
*/

DX::Object::Object(Graphic* graphic)
	:Actor(graphic, ActorKind::Object), m_mesh(nullptr), m_isUnlit(false), m_outlineMode(false), m_collider(nullptr), m_meshOutline(nullptr), m_enablePick(true)
{
	transform = new Transform();
	auto layout = graphic->GetLayout();
	vs = new VShader(graphic->Device(), "StdVS.cso", layout.data(), layout.size());
	ps = new PShader(graphic->Device(), "StdPS.cso");

	vs->AddCB(graphic->Device(), 0, 1, sizeof(SHADER_STD_TRANSF));
	ps->AddCB(graphic->Device(), SHADER_REG_CB_UNLIT, 1, sizeof(XMFLOAT4));

	m_material = new SHADER_MATERIAL(XMFLOAT3(0.6, 0.6, 0.6), 0.4, XMFLOAT3(0.6, 0.6, 0.6), XMFLOAT3(1.0, 1.0, 1.0));
	ps->AddCB(graphic->Device(), SHADER_REG_CB_MATERIAL, 1, sizeof(SHADER_MATERIAL));
	ps->WriteCB(graphic->DContext(), SHADER_REG_CB_MATERIAL, m_material);

	blendState = new BlendState(graphic->Device(), nullptr);
	dsState = new DepthStencilState(graphic->Device(), nullptr);
	rsState = new RasterizerState(graphic->Device(), nullptr);

	D3D11_DEPTH_STENCIL_DESC outlineMaskDesc = CD3D11_DEPTH_STENCIL_DESC(CD3D11_DEFAULT());
	outlineMaskDesc.DepthFunc = D3D11_COMPARISON_NEVER;
	outlineMaskDesc.StencilEnable = true;
	outlineMaskDesc.StencilWriteMask = 0xff;
	outlineMaskDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	outlineMaskDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_REPLACE;
	m_outlineMaskDSState = new DepthStencilState(graphic->Device(), &outlineMaskDesc);
	D3D11_DEPTH_STENCIL_DESC outlineRenderDesc = CD3D11_DEPTH_STENCIL_DESC(CD3D11_DEFAULT());
	outlineRenderDesc.DepthEnable = false;
	outlineRenderDesc.StencilEnable = true;
	outlineRenderDesc.StencilReadMask = 0xff;
	outlineRenderDesc.FrontFace.StencilFunc = D3D11_COMPARISON_NOT_EQUAL;
	outlineRenderDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	m_outlineRenderDSState = new DepthStencilState(graphic->Device(), &outlineRenderDesc);
}

Object::~Object()
{
	delete transform;
	delete vs;
	delete ps;

	delete dsState;
	delete blendState;
	delete rsState;

	delete m_material;
}

void Object::Update()
{
	if (!m_enable)
		return;

	UpdateBound();
	UpdateCollider();
}

void Object::UpdateBound()
{
	if (!m_mesh)
		return;

	XMFLOAT3 boundlMinPt;
	XMFLOAT3 boundlMaxPt;
	m_mesh->GetLBound(&boundlMinPt, &boundlMaxPt);
	XMMATRIX world = transform->WorldMatrix();
	XMFLOAT3 wMinPt = Multiply(boundlMinPt, world);
	XMFLOAT3 wMaxPt = Multiply(boundlMaxPt, world);
	bound.p = transform->GetPos();
	bound.rad = Length(wMinPt- wMaxPt) * 0.5f;
}

void Object::UpdateCollider()
{
	if (!m_collider)
		return;

	m_collider->Translate(transform->GetPos());
	m_collider->SetRotate(transform->GetForward(), transform->GetUp());
	//m_collider->SetScale(transform->GetScale());
}

Geometrics::Sphere DX::Object::Bound()
{
	return bound;
}

int DX::Object::Layer() const
{
	return layer;
}

void DX::Object::SetLayer(int l)
{
	layer = l;
}

void DX::Object::GetMaterial(SHADER_MATERIAL* material)
{
	*material = *m_material;
}

void DX::Object::GetMainTex(ID3D11ShaderResourceView** ppSRV)
{
	*ppSRV = m_mainTex;
}

void DX::Object::GetNormal(ID3D11ShaderResourceView** ppNormal)
{
	*ppNormal = m_normal;
}


bool Object::IsUnlit() {
	return m_isUnlit;
}
void DX::Object::SetUnlit(bool isUnlit)
{
	m_isUnlit = isUnlit;
	XMFLOAT4 unlitPassData(isUnlit ? 1 : 0, 0, 0, 0);
	ps->WriteCB(m_graphic->DContext(), SHADER_REG_CB_UNLIT, &unlitPassData);
}

void DX::Object::SetShape(Mesh* shape)
{
	if (m_mesh)
		delete m_mesh;

	m_mesh = shape;

	m_meshOutline = new Mesh(shape);
}

void DX::Object::SetCollider(Collider* collider)
{
	if (m_collider)
		delete m_collider;

	m_collider = collider;
}

void DX::Object::SetOutlineColor(DirectX::XMFLOAT4 color)
{
	m_meshOutline->SetColor(color);
}


void Object::Visualize()
{

	//if (IsInsideFrustum(CameraMgr::Instance()->Main()->GetFrustum()))
	//	Debugging::Instance()->Mark(bound.p, bound.rad, Colors::LightGreen);
}


void Object::Render()
{
	if (!m_enable)
		return;

	Camera* curCam = (Camera*)m_graphic->MainCamera();
	

	if (curCam && IsInsideFrustum(curCam->GetFrustum()))
	{
		auto vmat = curCam->VMat();
		auto pmat = curCam->ProjMat();

		const SHADER_STD_TRANSF STransformation(transform->WorldMatrix(), vmat, pmat, 1, 1000, XM_PIDIV2, 1);
		vs->WriteCB(m_graphic->DContext(), 0, &STransformation);

		vs->Apply(m_graphic);
		ps->Apply(m_graphic);

		blendState->Apply(m_graphic);
		rsState->Apply(m_graphic);



		if (m_outlineMode)//pass1
		{
			m_outlineMaskDSState->Apply(m_graphic);
			m_mesh->Apply(m_graphic);
		}

		dsState->Apply(m_graphic);
		m_mesh->Apply(m_graphic);

		if (m_outlineMode)//pass2
		{
			
			m_outlineRenderDSState->Apply(m_graphic);

			auto oriUnlit = IsUnlit();
			auto oriScale = transform->GetScale();

			SetUnlit(true);
			transform->SetScale(oriScale * 1.05);
			const SHADER_STD_TRANSF outlineTransformation(transform->WorldMatrix(), vmat, pmat, 1, 1000, XM_PIDIV2, 1);
			transform->SetScale(oriScale);

			vs->WriteCB(m_graphic->DContext(), 0, &outlineTransformation);
			m_meshOutline->Apply(m_graphic);

			SetUnlit(oriUnlit);


		}

		//m_graphic->DContext()->ClearDepthStencilView(m_graphic->DSV(), D3D11_CLEAR_STENCIL, NULL, 0);
	}

}

bool Object::IsInsideFrustum(const Frustum* frustum) const
{
	if (!frustum || frustum->skip)
		return true;

	return (
		IntersectInPlaneSphere(frustum->right, bound) &&
		IntersectInPlaneSphere(frustum->left, bound) &&
		IntersectInPlaneSphere(frustum->top, bound) &&
		IntersectInPlaneSphere(frustum->bottom, bound) &&
		IntersectInPlaneSphere(frustum->front, bound) &&
		IntersectInPlaneSphere(frustum->back, bound));
}


void DX::Object::EnablePick(bool enable)
{
	m_enablePick = enable;
}

bool Object::IsPicking(Geometrics::Ray ray, DirectX::XMFLOAT3& hit) const
{
	if (!m_enablePick)
		return false;

	if (!m_collider)
	{
		hit = transform->GetPos();
		return IntersectRaySphere(ray, bound);
	}

	return m_collider->IsHit(ray, &hit);
}

