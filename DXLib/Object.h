#pragma once

#include "Actor.h"
#include "Network.h"
#include "Geometrics.h"
#include <memory>

namespace DX {

	struct SHADER_MATERIAL;
	struct Frustum;
	class Transform;
	class Mesh;
	class Collider;
	class VShader;
	class PShader;
	class BlendState;
	class DepthStencilState;
	class RasterizerState;
	class Graphic;
	class Camera;

	class DXLIB_DLL Object : public IDebug ,public Actor
	{
	protected:

		//component
		std::unique_ptr<Transform> m_transform;
		std::unique_ptr<Mesh> m_mesh;
		std::unique_ptr<VShader> m_vs;
		std::unique_ptr<PShader> m_ps;
		std::unique_ptr<BlendState> m_blendState = nullptr;
		std::unique_ptr<RasterizerState> m_rsState = nullptr;
		std::unique_ptr<DepthStencilState> m_dsState = nullptr;
		std::unique_ptr<Collider> m_collider;
		bool m_isUnlit;
		bool m_enablePick;

		//outline
		std::unique_ptr<DepthStencilState> m_outlineMaskDSState = nullptr;
		std::unique_ptr<DepthStencilState> m_outlineRenderDSState = nullptr;
		std::unique_ptr<Mesh> m_meshOutline;

	public:

		Object(Graphic* graphic);
		virtual ~Object();

		void Update() override;
		void Render() override;
	
		void EnablePick(bool enable);
		virtual bool IsPicking(Geometrics::Ray ray, DirectX::XMFLOAT3& hit)const;
		virtual void UpdateBound();
		virtual void UpdateCollider();

		Geometrics::Sphere Bound();
		int Layer()const;
		void SetLayer(int l);
		void GetMaterial(SHADER_MATERIAL* pMaterial);
		void GetMainTex(ID3D11ShaderResourceView** pSRV);
		void GetNormal(ID3D11ShaderResourceView** pNormal);

		bool IsUnlit();
		void SetUnlit(bool isUnlit);
		void SetShape(std::unique_ptr<Mesh> shape);
		void SetCollider(std::unique_ptr<Collider> collider);
		Transform* GetTransform() { return m_transform.get(); }
		Mesh* GetShape() { return m_mesh.get(); }
		Collider* GetCollider() { return m_collider.get(); }

		void SetOutlineColor(DirectX::XMFLOAT4 color);
		bool m_outlineMode;

		std::unique_ptr<SHADER_MATERIAL> m_material;
		ID3D11ShaderResourceView* m_mainTex;
		ID3D11ShaderResourceView* m_normal;

		void Visualize() override;

		virtual bool IsInsideFrustum(const Frustum* frustum) const;

		void SetRenderStep(signed int step);

		int layer;

		Geometrics::Sphere bound;



	};
}

