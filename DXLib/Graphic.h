#pragma once
#include <unordered_map>
#include <unordered_set>
#include <DirectXMath.h>
#include "Actor.h"


namespace DX
{
	class VertexLayout;
	class Camera;
	class Object;

	class DXLIB_DLL Graphic
	{
	public:
		Graphic(HWND _hwnd, int msaa=1);
		virtual ~Graphic();

		virtual void Update(float spf);
		void BindView();
		ID3D11Device* Device() const ;
		ID3D11DeviceContext* DContext() const ;
		ID3D11Texture2D* DepthBuffer();
		ID3D11Texture2D* BackBuffer();
		ID3D11DepthStencilView* DSV();
		ID3D11RenderTargetView* RTV();
		HWND GetHWND() const;
		RECT GetWndSize() const;

		std::vector<D3D11_INPUT_ELEMENT_DESC> GetLayout();

		void CreateActor(ActorKind kind, Actor** out);
		std::vector<Actor*> GetActors(ActorKind kind) const;
		Actor* GetActor(std::string id)const;
		Camera* MainCamera() const;
		void SetMainCamera(Camera* cam);

		//movement
		void EnableCamMovement(bool enable);
		void KeyPress(char c, bool press=true);
		void MouseLClick(bool click = true);
		void MouseRClick(bool click = true);
		void MousePT(float x, float y);

		Object* PickObj(DirectX::XMFLOAT3* hit) const;

	protected:
		Graphic() = delete;

		HWND m_hwnd;

		ID3D11Device* m_device;
		ID3D11DeviceContext* m_dContext;

		ID3D11Texture2D* m_backBuffer;
		ID3D11Texture2D* m_depthStencilBuffer;
		D3D11_VIEWPORT m_viewport;
		IDXGISwapChain* m_swapchain;
		ID3D11RenderTargetView* m_rtv;
		ID3D11DepthStencilView* m_dsView;
		ID3D11RasterizerState* m_rasterizerState;

		std::vector<D3D11_INPUT_ELEMENT_DESC> m_vertLayout;

		std::unordered_map<ActorKind, std::vector<Actor*>> m_actors;

		Camera* m_mainCamera;

		Object* m_curPicked;
		DirectX::XMFLOAT3 m_pickHit;
		
		bool m_enableCamMovement;
		std::unordered_set<char> m_inputKeys;
		bool m_mouseLClicked;
		bool m_mouseRClicked;
		float m_mouseX;
		float m_mouseY;

		virtual void UpdateCamMovement(float spf);
	};



}

