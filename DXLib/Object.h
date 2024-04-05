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
		Transform* transform;
		Mesh* m_mesh;
		VShader* vs;
		PShader* ps;
		BlendState* blendState = nullptr;
		RasterizerState* rsState = nullptr;
		DepthStencilState* dsState = nullptr;
		Collider* m_collider;
		bool m_isUnlit;
		bool m_enablePick;

		//outline
		DepthStencilState* m_outlineMaskDSState = nullptr;
		DepthStencilState* m_outlineRenderDSState = nullptr;
		Mesh* m_meshOutline;

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
		void SetShape(Mesh* shape);
		void SetCollider(Collider* collider);
		Transform* GetTransform() { return transform; }
		Mesh* GetShape() { return m_mesh; }
		Collider* GetCollider() { return m_collider; }

		void SetOutlineColor(DirectX::XMFLOAT4 color);
		bool m_outlineMode;

		SHADER_MATERIAL* m_material;
		ID3D11ShaderResourceView* m_mainTex;
		ID3D11ShaderResourceView* m_normal;

		void Visualize() override;

		virtual bool IsInsideFrustum(const Frustum* frustum) const;

		void SetRenderStep(signed int step);

		int layer;

		Geometrics::Sphere bound;



	};
}

