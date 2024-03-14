

#include "pch.h"

#include "Graphic.h"
#include "MathHelper.h"

#include "Object.h"
#include "Light.h"
#include "Camera.h"
#include "Text.h"
#include "CubeMesh.h"
#include "ShaderReg.h"
#include "Transform.h"
#include "CubeCollider.h"

namespace DX {


	Graphic::Graphic(HWND _hwnd, int msaa)
		:m_mainCamera(nullptr), m_mouseLClicked(false), m_mouseRClicked(false),m_mouseX(0), m_mouseY(0), m_enableCamMovement(false), m_hwnd(_hwnd), m_curPicked(nullptr)
	{
		assert(msaa == 1 || msaa == 2 || msaa == 4 || msaa == 8 || msaa == 16);

		RECT rc = GetWndSize();
		int iWidth = rc.right - rc.left;
		int iHeight = rc.bottom - rc.top;

		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

		scd.BufferDesc.Width = (UINT)iWidth;
		scd.BufferDesc.Height = (UINT)iHeight;
		scd.BufferDesc.RefreshRate.Numerator = 60;
		scd.BufferDesc.RefreshRate.Denominator = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		scd.SampleDesc.Count = msaa;
		scd.SampleDesc.Quality = 0;

		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.BufferCount = 1;
		scd.OutputWindow = m_hwnd;
		scd.Windowed = TRUE;
		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			D3D11_CREATE_DEVICE_DEBUG,
			NULL,
			0,
			D3D11_SDK_VERSION,
			&scd,
			&m_swapchain,
			&m_device,
			NULL,
			&m_dContext);
		r_assert(hr);

		hr = m_swapchain->GetBuffer(
			0,
			__uuidof(ID3D11Texture2D),
			reinterpret_cast<void**>(&m_backBuffer));
		r_assert(hr);

		hr = m_device->CreateRenderTargetView(
			m_backBuffer,
			nullptr,
			&m_rtv);
		r_assert(hr);

#pragma region Depth&Stencil Buffer

		D3D11_TEXTURE2D_DESC ds_desc;
		ds_desc.Width = scd.BufferDesc.Width;
		ds_desc.Height = scd.BufferDesc.Height;
		ds_desc.MipLevels = 1;
		ds_desc.ArraySize = 1;
		// TYPELESS instead of UNORM for copying data
		ds_desc.Format = DXGI_FORMAT_R24G8_TYPELESS;
		ds_desc.SampleDesc = scd.SampleDesc;
		ds_desc.Usage = D3D11_USAGE_DEFAULT;
		ds_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		ds_desc.CPUAccessFlags = 0;
		ds_desc.MiscFlags = 0;

		hr = m_device->CreateTexture2D(
			&ds_desc,
			nullptr,
			&m_depthStencilBuffer);
		r_assert(hr);

		D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc;
		ZeroMemory(&dsv_desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		dsv_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsv_desc.Flags = 0;
		if (msaa == 1)
		{
			dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			dsv_desc.Texture2D.MipSlice = 0;
		}
		else
		{
			dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		}
		hr = m_device->CreateDepthStencilView(
			m_depthStencilBuffer,
			&dsv_desc,
			&m_dsView);
		r_assert(hr);
		m_dContext->OMSetRenderTargets(1, &m_rtv, m_dsView);

#pragma endregion

#pragma region Viewport

		//map vertex positions in clip space into render target positions
		ZeroMemory(&m_viewport, sizeof(D3D11_VIEWPORT));
		m_viewport.TopLeftX = 0;
		m_viewport.TopLeftY = 0;
		m_viewport.Width = scd.BufferDesc.Width;
		m_viewport.Height = scd.BufferDesc.Height;
		m_viewport.MinDepth = 0.0f;
		m_viewport.MaxDepth = 1.0f;

		m_dContext->RSSetViewports(1, &m_viewport);
#pragma endregion

#pragma region Rasterizer
		D3D11_RASTERIZER_DESC rs_desc;
		ZeroMemory(&rs_desc, sizeof(D3D11_RASTERIZER_DESC));
		rs_desc.FillMode = D3D11_FILL_SOLID;
		rs_desc.CullMode = D3D11_CULL_BACK;
		hr = m_device->CreateRasterizerState(&rs_desc, &m_rasterizerState);
		r_assert(hr);
		m_dContext->RSSetState(m_rasterizerState);
#pragma endregion

#pragma region Sampler
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(D3D11_SAMPLER_DESC));
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		FLOAT black[4] = { 0,0,0,1 };
		sampDesc.BorderColor[0] = 0;
		sampDesc.BorderColor[1] = 0;
		sampDesc.BorderColor[2] = 0;
		sampDesc.BorderColor[3] = 1;
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		ID3D11SamplerState* samp;
		Device()->CreateSamplerState(&sampDesc, &samp);
		DContext()->PSSetSamplers(SHADER_REG_SAMP_POINT, 1, &samp);
		samp->Release();
#pragma endregion


		m_vertLayout.push_back({"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0});
		m_vertLayout.push_back({"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		m_vertLayout.push_back({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		m_vertLayout.push_back({ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		
	}

	Graphic::~Graphic()
	{
		m_backBuffer->Release();
		m_device->Release();
		m_dContext->Release();
		m_swapchain->Release();

		m_rtv->Release();
		m_dsView->Release();
		m_depthStencilBuffer->Release();
		m_rasterizerState->Release();

	}

	void Graphic::Update(float spf)
	{
		//find pick obj
		{
			Geometrics::Ray camRay;
			m_mainCamera->Pick({ m_mouseX, m_mouseY }, &camRay);

			m_pickHit = NOWHERE;
			m_curPicked = nullptr;
			float closestDist = FLT_MAX;
			for (auto a : m_actors.at(ActorKind::Object))
			{
				Object* obj = (Object*)a;
				XMFLOAT3 hit;

				if (obj->IsPicking(camRay, hit))
				{
					float dist = SqrLength(hit - m_mainCamera->transform->GetPos());
					if (closestDist > dist)
					{
						closestDist = dist;
						m_curPicked = obj;
						m_pickHit = hit;
					}
				}
			}

		}

		//main loop
		for (auto it = m_actors.begin(); it!=m_actors.end(); ++it)
		{
			if (it->second.empty())
			{
				it = m_actors.erase(it);
				continue;
			}
			
			for (int i = 0; i < it->second.size();)
			{
				Actor* curActor = it->second[i];
				if (curActor->m_isRelease)
				{
					if (curActor == m_mainCamera)
					{
						m_mainCamera = nullptr;
					}

					delete curActor;
					it->second.erase(it->second.begin() + i);
				}
				else
					i++;
			}


			for (int i = 0; i < it->second.size(); i++)
			{
				it->second[i]->Update();
			}
			for (int i = 0; i < it->second.size();i++)
			{
				it->second[i]->Render();
			}
			

		}


		//camera movement
		UpdateCamMovement(spf);



		m_swapchain->Present(1, 0);

		const float black[4] = { 1,1,1,0 };
		m_dContext->ClearRenderTargetView(m_rtv, black);
		m_dContext->ClearDepthStencilView(m_dsView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
	void Graphic::BindView()
	{
		m_dContext->OMSetRenderTargets(1, &m_rtv, m_dsView);
	}
	ID3D11Device* Graphic::Device()const
	{
		return m_device;
	}
	ID3D11DeviceContext* Graphic::DContext()const
	{
		return m_dContext;
	}
	ID3D11Texture2D* Graphic::DepthBuffer()
	{
		return m_depthStencilBuffer;
	}
	ID3D11Texture2D* Graphic::BackBuffer()
	{
		return m_backBuffer;
	}
	ID3D11DepthStencilView* Graphic::DSV()
	{
		return m_dsView;
	}
	ID3D11RenderTargetView* Graphic::RTV()
	{
		return m_rtv;
	}

	HWND Graphic::GetHWND()const
	{
		return m_hwnd;
	}

	RECT Graphic::GetWndSize() const
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);
		return rc;
	}

	std::vector<D3D11_INPUT_ELEMENT_DESC> Graphic::GetLayout()
	{
		return m_vertLayout;
	}

	void Graphic::CreateActor(ActorKind kind, Actor** out)
	{
		switch (kind)
		{
		case ActorKind::Object:
		{
			Mesh* defaultMesh = new CubeMesh(m_device);

			auto newObject = new Object(this);

			newObject->SetShape(defaultMesh);
			newObject->SetUnlit(false);
			newObject->SetCollider(new CubeCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(0.5, 0.5, 0.5)));

			*out = newObject;
		}
		break;
		case ActorKind::Camera:

		{
			RECT rc;
			GetClientRect(m_hwnd, &rc);
			*out = new Camera(this, FRAME_KIND_PERSPECTIVE, rc.right-rc.left, rc.bottom-rc.top, 1.0f, 1000.0f, XM_PIDIV2, 1, true);

			if (!m_mainCamera)
			{
				m_mainCamera = (Camera*)*out;
			}
		}
			break;
		case ActorKind::Light_Direction:

			*out = new DirectionalLight(this, 0, XMFLOAT3(0.25, 0.25, 0.25),
				XMFLOAT3(0.8, 0.8, 0.8),
				XMFLOAT3(0.7, 0.7, 0.7),
				0.7f,
				Normalize(XMFLOAT3(0, -1, 0)));

			break;
		case ActorKind::Light_Point:

			*out = new PointLight(this, 0, XMFLOAT3(0.25, 0.25, 0.25),
				XMFLOAT3(0.8, 0.8, 0.8),
				XMFLOAT3(0.7, 0.7, 0.7),
				0.7f,
				XMFLOAT3(0, 0, 0),
				XMFLOAT3(0, 0, 0));

				break;
		case ActorKind::Light_Spot:

			*out = new DirectionalLight(this, 0, XMFLOAT3(0.25, 0.25, 0.25),
				XMFLOAT3(0.8, 0.8, 0.8),
				XMFLOAT3(0.7, 0.7, 0.7),
				0.7f,
				Normalize(XMFLOAT3(1, 0, 0)));

				break;

		case ActorKind::Text:

			*out = new Text(this);

			break;
		default:

			assert(false && "unidentified actor kind");
			break;
		}

		m_actors[kind].push_back(*out);
	}

	std::vector<Actor*> Graphic::GetActors(ActorKind kind) const
	{
		return m_actors.at(kind);
	}

	Actor* Graphic::GetActor(std::string id) const
	{
		for (auto it : m_actors)
		{
			for (auto a : it.second)
			{
				if (a->m_id == id)
					return a;
			}
		}

		return nullptr;
	}

	Camera* Graphic::MainCamera()const
	{
		return m_mainCamera;
	}

	void Graphic::SetMainCamera(Camera* cam)
	{
		m_mainCamera = cam;
	}

	void Graphic::EnableCamMovement(bool enable)
	{
		m_enableCamMovement = enable;
	}

	void Graphic::KeyPress(char c, bool press)
	{
		if (press)
		{
			m_inputKeys.insert(c);
		}
		else
		{
			m_inputKeys.erase(c);
		}
	}

	void Graphic::MouseLClick(bool click)
	{
		m_mouseLClicked = click;
	}

	void Graphic::MouseRClick(bool click)
	{
		m_mouseRClicked = click;
	}

	void Graphic::MousePT(float x, float y)
	{
		m_mouseX = x;
		m_mouseY = y;
	}

	Object* Graphic::PickObj(DirectX::XMFLOAT3* hit) const
	{
		if (hit)
			*hit = m_pickHit;

		return m_curPicked;
	}

	void Graphic::UpdateCamMovement(float spf)
	{
		if (m_mainCamera && m_enableCamMovement)
		{
			auto cam = (Camera*)m_mainCamera;
			XMFLOAT3 newPos = cam->transform->GetPos();
			XMFLOAT3 right = cam->transform->GetRight();
			XMFLOAT3 forward = cam->transform->GetForward();
			const float speed = 50;


			if (m_inputKeys.find('A') != m_inputKeys.end()) {

				newPos = XMFLOAT3(newPos.x - right.x * speed * spf, newPos.y - right.y * speed * spf, newPos.z - right.z * speed * spf);
			}
			else if (m_inputKeys.find('D') != m_inputKeys.end()) {

				newPos = XMFLOAT3(newPos.x + right.x * speed * spf, newPos.y + right.y * speed * spf, newPos.z + right.z * speed * spf);
			}
			if (m_inputKeys.find('S') != m_inputKeys.end()) {

				newPos = XMFLOAT3(newPos.x - forward.x * speed * spf, newPos.y - forward.y * speed * spf, newPos.z - forward.z * speed * spf);
			}
			else if (m_inputKeys.find('W') != m_inputKeys.end()) {

				newPos = XMFLOAT3(newPos.x + forward.x * speed * spf, newPos.y + forward.y * speed * spf, newPos.z + forward.z * speed * spf);
			}
			static float angleX = 0;
			static float angleY = 0;
			static XMFLOAT2 prevMousePt;
			const float angleSpeed = 3.141592f * 0.2f;
			if (m_mouseRClicked)
			{
				angleY += angleSpeed * spf * (m_mouseX - prevMousePt.x);
				angleX += angleSpeed * spf * (m_mouseY - prevMousePt.y);
			}
			prevMousePt.x = m_mouseX;
			prevMousePt.y = m_mouseY;
			const XMMATRIX rotMat = XMMatrixRotationX(angleX) * XMMatrixRotationY(angleY);
			cam->transform->SetTranslation(newPos);
			XMFLOAT3 f = DX::MultiplyDir(FORWARD, rotMat);
			XMFLOAT3 u = DX::MultiplyDir(UP, rotMat);
			cam->transform->SetRot(f, u);
		}
	}


}
	


