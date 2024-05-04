#pragma once
#include <unordered_map>
#include <unordered_set>
#include <DirectXMath.h>
#include <memory>
#include "DXUtility.h"
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
		ID3D11Texture2D* DepthBuffer()const ;
		ID3D11Texture2D* BackBuffer();
		ID3D11DepthStencilView* DSV()const;
		ID3D11RenderTargetView* RTV();
		HWND GetHWND() const;
		RECT GetWndSize() const;
		void SetBackgroundColor(DirectX::XMFLOAT4 color);

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
		void MouseWheel(int delta);
		float m_camAngleX;
		float m_camAngleY;

		Object* PickObj(DirectX::XMFLOAT3* hit) const;
		DirectX::XMFLOAT2 Dir2Screen(DirectX::XMFLOAT3 dir);

	protected:
		Graphic() = delete;

		HWND m_hwnd;

		std::unique_ptr<ID3D11Device, Delete_Release> m_device;
		std::unique_ptr<ID3D11DeviceContext,Delete_Release> m_dContext;

		std::unique_ptr<ID3D11Texture2D, Delete_Release> m_backBuffer;
		std::unique_ptr<ID3D11Texture2D, Delete_Release> m_depthStencilBuffer;
		D3D11_VIEWPORT m_viewport;
		std::unique_ptr<IDXGISwapChain,Delete_Release> m_swapchain;
		std::unique_ptr<ID3D11RenderTargetView,Delete_Release> m_rtv;
		std::unique_ptr<ID3D11DepthStencilView,Delete_Release> m_dsView;
		std::unique_ptr<ID3D11RasterizerState, Delete_Release> m_rasterizerState;
		DirectX::XMFLOAT4 m_bkgColor;

		std::vector<D3D11_INPUT_ELEMENT_DESC> m_vertLayout;

		std::unordered_map<ActorKind, std::vector<Actor*>> m_actors;

		Camera* m_mainCamera;
		DirectX::XMFLOAT2 m_prevMousePt;

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

