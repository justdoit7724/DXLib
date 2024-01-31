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
		DepthStencilState* dsState = nullptr;
		RasterizerState* rsState = nullptr;
		std::shared_ptr <Collider> m_collider;
		bool m_isUnlit;

		friend class Graphic;
		Object(Graphic* graphic);
		virtual ~Object();

	public:

		void Update() override;
		void Render() override;
	
		virtual bool IsPicking(Geometrics::Ray ray)const;
		virtual void UpdateBound();
		virtual void UpdateCollider();

		Geometrics::Sphere Bound();
		int Layer()const;
		void SetLayer(int l);
		void GetMaterial(SHADER_MATERIAL* pMaterial);
		void GetMainTex(ID3D11ShaderResourceView** pSRV);
		void GetNormal(ID3D11ShaderResourceView** pNormal);

		void SetUnlit(bool isUnlit);
		void SetShape(Mesh* shape);
		Transform* GetTransform() { return transform; }
		Mesh* GetShape() { return m_mesh; }



		SHADER_MATERIAL* m_material;
		ID3D11ShaderResourceView* m_mainTex;
		ID3D11ShaderResourceView* m_normal;

		void Visualize() override;

		virtual bool IsInsideFrustum(const Frustum* frustum) const;

		bool enabled = true;
		bool show = true;
		int layer;

		Geometrics::Sphere bound;

	public:
		void SetEnabled(bool e) { enabled = e; }
		void SetShow(bool s) { show = s; }




	};
}

