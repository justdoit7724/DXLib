#pragma once
#include <unordered_map>
#include <unordered_set>
#include "Actor.h"


namespace DX
{
	class VertexLayout;

	class DXLIB_DLL Graphic
	{
	public:
		Graphic(HWND _hwnd, int msaa=1);
		~Graphic();

		void Present(double spf);
		void BindView();
		ID3D11Device* Device() const ;
		ID3D11DeviceContext* DContext() const ;
		ID3D11Texture2D* DepthBuffer();
		ID3D11Texture2D* BackBuffer();
		ID3D11DepthStencilView* DSV();
		ID3D11RenderTargetView* RTV();
		HWND GetHWND();

		void CreateActor(ActorKind kind, Actor** out);
		std::unordered_map<ActorKind, std::vector<Actor*>> GetAllActors() const;
		Actor* MainCamera() const;
		void SetMainCamera(Actor* cam);

		//movement
		void EnableCamMovement(bool enable);
		void KeyPress(char c, bool press=true);
		void MouseLClick(bool click = true);
		void MouseRClick(bool click = true);
		void MousePT(float x, float y);

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

		std::unordered_map<ActorKind, std::vector<Actor*>> m_actors;

		Actor* m_mainCamera;
		
		
		bool m_enableCamMovement;
		std::unordered_set<char> m_inputKeys;
		bool m_mouseLClicked;
		bool m_mouseRClicked;
		float m_mouseX;
		float m_mouseY;

		virtual void UpdateCamMovement(float spf);
	};


	const DXLIB_DLL VertexLayout& D3DLayout_Simple();
	const DXLIB_DLL VertexLayout& D3DLayout_Std();

}

