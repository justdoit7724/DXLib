#pragma once


#define LIGHT_ENABLED 1
#define LIGHT_DISABLED 0
#define LIGHT_MAX_EACH 3

namespace DX {
	
	//struct Vertex {
	//	DirectX::XMFLOAT3 pos;
	//	DirectX::XMFLOAT2 tex;
	//	DirectX::XMFLOAT3 n;
	//	//DirectX::XMFLOAT3 tangent;

	//	Vertex() :pos(DirectX::XMFLOAT3(0, 0, 0)), n(DirectX::XMFLOAT3(0, 0, 0)), tex(DirectX::XMFLOAT2(0, 0)) {}
	//	Vertex(const Vertex& v)
	//	{
	//		pos = v.pos;
	//		n = v.n;
	//		tex = v.tex;
	//	}
	//	Vertex(DirectX::XMFLOAT3 _pos)
	//	{
	//		pos = _pos;
	//		n = DirectX::XMFLOAT3(0, 0, 0);
	//		tex = DirectX::XMFLOAT2(0, 0);
	//	}
	//	Vertex(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 n, DirectX::XMFLOAT2 tex, DirectX::XMFLOAT3 tangent) :pos(pos), n(n), tex(tex) {}
	//};

	struct SHADER_STD_TRANSF
	{
		DirectX::XMMATRIX w;
		DirectX::XMMATRIX v;
		DirectX::XMMATRIX p;
		DirectX::XMMATRIX n;
		float fNear;
		float fFar;
		float fAspect;
		float fRatio;

		SHADER_STD_TRANSF(DirectX::XMMATRIX v, DirectX::XMMATRIX p, float fNear, float fFar, float fAspect, float fRatio)
			:v(v), p(p), fNear(fNear), fFar(fFar), fAspect(fAspect), fRatio(fRatio)
		{
			const DirectX::XMMATRIX& mId = DirectX::XMMatrixIdentity();
			w = mId;
			n = mId;
		}
		SHADER_STD_TRANSF(DirectX::XMMATRIX world, DirectX::XMMATRIX v, DirectX::XMMATRIX p, float fNear, float fFar, float fAspect, float fRatio)
			:w(world), v(v), p(p), fNear(fNear), fFar(fFar), fAspect(fAspect), fRatio(fRatio)
		{
			DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(world);
			n = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(&det, world));
		}
	};
	
	struct SHADER_DIRECTIONAL_LIGHT {

		SHADER_DIRECTIONAL_LIGHT() {


			ZeroMemory(ambient, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);
			ZeroMemory(diffuse, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);
			ZeroMemory(specular, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);
			ZeroMemory(dir, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);
			ZeroMemory(enabled, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);
			ZeroMemory(intensity, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);

			for (int i = 0; i < LIGHT_MAX_EACH; ++i)
			{
				enabled[i] = DirectX::XMFLOAT4(LIGHT_DISABLED, 0, 0, 0);
			}
		}

		DirectX::XMFLOAT4 ambient[LIGHT_MAX_EACH];
		DirectX::XMFLOAT4 diffuse[LIGHT_MAX_EACH];
		DirectX::XMFLOAT4 specular[LIGHT_MAX_EACH];
		DirectX::XMFLOAT4 dir[LIGHT_MAX_EACH];
		DirectX::XMFLOAT4 enabled[LIGHT_MAX_EACH]; // enable
		DirectX::XMFLOAT4 intensity[LIGHT_MAX_EACH];

	};
	struct SHADER_POINT_LIGHT {

		SHADER_POINT_LIGHT()
		{

			ZeroMemory(ambient, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);
			ZeroMemory(diffuse, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);
			ZeroMemory(specular, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);
			ZeroMemory(pos, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);
			ZeroMemory(info, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);
			ZeroMemory(att, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);
			ZeroMemory(intensity, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);

			for (int i = 0; i < LIGHT_MAX_EACH; ++i)
			{
				info[i].x = LIGHT_DISABLED;
			}
		}

		DirectX::XMFLOAT4 ambient[LIGHT_MAX_EACH];
		DirectX::XMFLOAT4 diffuse[LIGHT_MAX_EACH];
		DirectX::XMFLOAT4 specular[LIGHT_MAX_EACH];
		DirectX::XMFLOAT4 pos[LIGHT_MAX_EACH];
		DirectX::XMFLOAT4 info[LIGHT_MAX_EACH]; // enable
		DirectX::XMFLOAT4 att[LIGHT_MAX_EACH];
		DirectX::XMFLOAT4 intensity[LIGHT_MAX_EACH];

	};
	struct SHADER_SPOT_LIGHT {

		SHADER_SPOT_LIGHT()
		{
			ZeroMemory(ambient, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);
			ZeroMemory(diffuse, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);
			ZeroMemory(specular, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);
			ZeroMemory(pos, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);
			ZeroMemory(info, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);
			ZeroMemory(dir, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);
			ZeroMemory(att, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);
			ZeroMemory(intensity, sizeof(DirectX::XMFLOAT4) * LIGHT_MAX_EACH);

			for (int i = 0; i < LIGHT_MAX_EACH; ++i)
			{
				info[i].x = LIGHT_DISABLED;
			}
		}

		DirectX::XMFLOAT4 ambient[LIGHT_MAX_EACH];
		DirectX::XMFLOAT4 diffuse[LIGHT_MAX_EACH];
		DirectX::XMFLOAT4 specular[LIGHT_MAX_EACH];
		DirectX::XMFLOAT4 pos[LIGHT_MAX_EACH];
		DirectX::XMFLOAT4 info[LIGHT_MAX_EACH]; // enabled,range,rad,spot
		DirectX::XMFLOAT4 dir[LIGHT_MAX_EACH];
		DirectX::XMFLOAT4 att[LIGHT_MAX_EACH];
		DirectX::XMFLOAT4 intensity[LIGHT_MAX_EACH];
	};

	struct SHADER_MATERIAL
	{
	private:
		DirectX::XMFLOAT4 diffuse;
		DirectX::XMFLOAT4 ambient;
		DirectX::XMFLOAT4 specular;

	public:
		SHADER_MATERIAL() {}
		SHADER_MATERIAL(DirectX::XMFLOAT3 d, float transparency, DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 s)
			:
			diffuse(DirectX::XMFLOAT4(d.x, d.y, d.z, transparency)),
			ambient(DirectX::XMFLOAT4(a.x, a.y, a.z, 0)),
			specular(DirectX::XMFLOAT4(s.x, s.y, s.z, 0))
		{}
		void SetTransparency(float t)
		{
			diffuse.w = t;
		}
		void SetSpecPower(float p)
		{
			specular.w = p;
		}
		void SetDiffuse(DirectX::XMFLOAT3 d)
		{
			diffuse.x = d.x;
			diffuse.y = d.y;
			diffuse.z = d.z;
		}
		void SetSpec(DirectX::XMFLOAT3 s)
		{
			specular.x = s.x;
			specular.y = s.y;
			specular.z = s.z;
		}
		void SetAmbient(DirectX::XMFLOAT3 a)
		{
			ambient.x = a.x;
			ambient.y = a.y;
			ambient.z = a.z;
		}
	};


}