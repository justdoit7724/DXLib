#pragma once

#include "Actor.h"
#include "LayerMask.h"
#include "Geometrics.h"

namespace DX
{
	enum FRAME_KIND {
		FRAME_KIND_PERSPECTIVE,
		FRAME_KIND_ORTHOGONAL
	};

	class Transform;
	class Buffer;

	struct Frustum
	{
		bool skip;
		Geometrics::PlaneInf front;
		Geometrics::PlaneInf back;
		Geometrics::PlaneInf right;
		Geometrics::PlaneInf left;
		Geometrics::PlaneInf top;
		Geometrics::PlaneInf bottom;

		Frustum() {}
	};

	class DXLIB_DLL Camera : public Actor
	{
	protected:
		friend class Graphic;
		Camera(const Graphic* graphic, FRAME_KIND frameKind, float screenWidth, float screenHeight, float nearPlane, float farPlane, float verticalViewRad, float aspectRatio, bool skipFrustum);

		

		void SetLayer(int i)
		{
			layer = i;
		}
		void AddLayer(int i)
		{
			layer |= i;
		}
		void SubtractLayer(int i)
		{
			layer ^= i;
		}
		int Layer()const { return layer; }

	public:
		~Camera();
		void SetFrame(const FRAME_KIND fKind, DirectX::XMFLOAT2 orthoSize, const float nearPlane, const float farPlane, const float verticalViewAngle, const float aspectRatio);
		void SetScale(float scale);
		float GetScale();
		void Update() override;

		const DirectX::XMMATRIX& VMat()const { return viewMat; }
		const DirectX::XMMATRIX& ProjMat()const { return projMat; }
		void Pick(DirectX::XMFLOAT2 scnPos, OUT Geometrics::Ray* ray)const;

		FRAME_KIND GetFrame()const { return curFrame; }
		DirectX::XMFLOAT2 GetSize()const { return m_size; }
		float GetN()const { return n; }
		float GetF()const { return f; }
		float GetVRad()const { return verticalRadian; }
		float GetAspectRatio()const { return aspectRatio; }

		const Frustum* GetFrustum()const { return &frustum; }
		Transform* transform;



	private:
		void SetView();
		void SetProj();

		DirectX::XMMATRIX projMat;
		DirectX::XMMATRIX viewMat;

		FRAME_KIND curFrame;
		DirectX::XMFLOAT2 m_size;
		float n, f;
		float verticalRadian;
		float aspectRatio;
		float m_scale;

		Frustum frustum;
		int layer = LAYER_ALL;


		Buffer* m_cbPos;
	};
}
