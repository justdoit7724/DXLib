#pragma once
#include "Actor.h"
#include "ShaderFormat.h"

namespace DX
{
	class Buffer;
class Transform;
class Camera;
class Object;
class VShader;
class BlendState;
class DepthStencilState;
class RasterizerState;
struct SHADER_POINT_LIGHT;
struct SHADER_SPOT_LIGHT;

	class DXLIB_DLL Light:public Actor
	{
	protected:
		DirectX::XMFLOAT3 ambient;
		DirectX::XMFLOAT3 diffuse;
		DirectX::XMFLOAT3 specular;
		std::unique_ptr<Buffer> m_cb;

		Light(const Graphic* graphic, int index, ActorKind lightKind);


	public:
		const int m_index;


		int ID() { return m_index; }
		const DirectX::XMFLOAT3& GetAmbient() { return ambient; }
		const DirectX::XMFLOAT3& GetDiffuse() { return diffuse; }
		const DirectX::XMFLOAT3& GetSpecular() { return specular; }
		virtual void SetAmbient(const DirectX::XMFLOAT3& a) = 0;
		virtual void SetDiffuse(const DirectX::XMFLOAT3& d) = 0;
		virtual void SetSpecular(const DirectX::XMFLOAT3& s) = 0;
		virtual void SetIntensity(float i) = 0;
		virtual void Enable(bool enable) = 0;
	};

	class DXLIB_DLL DirectionalLight : public Light
	{
	private:
		SHADER_DIRECTIONAL_LIGHT m_data;
		
		friend class Graphic;
		DirectionalLight(const Graphic* graphic, int id, DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 d, DirectX::XMFLOAT3 s, float intensity, DirectX::XMFLOAT3 dir);

	public:
		void SetAmbient(const DirectX::XMFLOAT3& a) override;
		void SetDiffuse(const DirectX::XMFLOAT3& d) override;
		void SetSpecular(const DirectX::XMFLOAT3& s) override;
		void SetIntensity(float i) override;
		void Enable(bool enable) override;

		void SetDir(DirectX::XMFLOAT3 d);
		DirectX::XMFLOAT3 GetDir()const;

		void Update()override;
	};

	class DXLIB_DLL PointLight : public Light
	{
	private:
		float range;
		DirectX::XMFLOAT3 att;

		SHADER_POINT_LIGHT m_data;

		friend class Graphic;
		PointLight(const Graphic* graphic, int id, DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 d, DirectX::XMFLOAT3 s, float intensity, DirectX::XMFLOAT3 att, DirectX::XMFLOAT3 pos);

	public:
		void SetAmbient(const DirectX::XMFLOAT3& a) override;
		void SetDiffuse(const DirectX::XMFLOAT3& d) override;
		void SetSpecular(const DirectX::XMFLOAT3& s) override;
		void SetIntensity(float i) override;
		void SetPos(DirectX::XMFLOAT3 p);
		void SetAtt(DirectX::XMFLOAT3 at);
		void Enable(bool enable) override;

		DirectX::XMFLOAT3 GetPos();

		void Update()override;
	};

	class DXLIB_DLL SpotLight : public Light
	{
	private:
		SHADER_SPOT_LIGHT m_data;

		float range;
		float spot;
		float rad;
		DirectX::XMFLOAT3 att;

		friend class Graphic;
		SpotLight(const Graphic* graphic, int id, DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 d, DirectX::XMFLOAT3 s, float range, float spot, float intensity, float rad, DirectX::XMFLOAT3 att, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 dir);

	public:
		void SetAmbient(const DirectX::XMFLOAT3& a) override;
		void SetDiffuse(const DirectX::XMFLOAT3& d) override;
		void SetSpecular(const DirectX::XMFLOAT3& s) override;
		void SetIntensity(float i) override;
		void SetPos(DirectX::XMFLOAT3 p);
		void SetDir(DirectX::XMFLOAT3 d);
		void SetRange(float r);
		void SetRad(float r);
		void SetSpot(float s);
		void SetAtt(DirectX::XMFLOAT3 at);
		void Enable(bool enable);


		DirectX::XMFLOAT3 GetPos();

		void Update()override;
	};

}

