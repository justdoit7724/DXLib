#pragma once

#define MARK_MAX 220

namespace DX
{

class Transform;
class Mesh;
class VShader;
class PShader;
class Buffer;
class DepthStencilState;
class BlendState;
class RasterizerState;
class Camera;
class IDebug;
struct SHADER_STD_TRANSF;
	class DXLIB_DLL Debugging
	{
	public:
		Debugging(ID3D11Device* device, ID3D11DeviceContext* dContext);

		void Mark(XMFLOAT3 pos, float radius = 1.0f, XMVECTORF32 color= g_XMOne);
		void MarkCube(XMFLOAT3 center, XMFLOAT3 forward, XMFLOAT3 up, XMFLOAT3 extent);
		void PtLine(XMFLOAT3 p1, XMFLOAT3 p2, XMVECTORF32 color= g_XMOne);
		void DirLine(XMFLOAT3 p1, XMFLOAT3 dir, float dist, XMVECTORF32 color= g_XMOne);

		void EnableGrid(ID3D11Device* device, float interval, int num = 100);
		void DisableGrid();

		void Visualize(IDebug* obj);

		~Debugging();

		void Enabled(bool b) { enabled = b; }
		void SetCamera(const Camera* cam);

		void Update(float spf);
		void Render(ID3D11DeviceContext* dContext, int iScnWidth, int iScnHeight);
	private:
		const Camera* debugCam = nullptr;

		bool enabled = true;

		struct MarkInfo {
			bool isDraw;
			XMFLOAT3 pos;
			float rad;
			XMVECTOR color;

			MarkInfo() :isDraw(false), pos(XMFLOAT3(0, 0, 0)), rad(1), color(g_XMOne) {}
		};
		UINT m_curMarkIdx = 0;
		Transform* m_markTransform;
		Mesh* m_markShape;
		MarkInfo m_marks[MARK_MAX];

		struct LineInfo {
			XMFLOAT3 p1, p2;
			XMVECTOR color;

			LineInfo() :p1(XMFLOAT3(0, 0, 0)), p2(XMFLOAT3(0, 0, 0)), color(g_XMOne) {}
			LineInfo(const XMFLOAT3 _p1, const XMFLOAT3 _p2, const XMVECTORF32 _c) {
				p1 = _p1;
				p2 = _p2;
				color = _c;
			}
		};
		std::vector<LineInfo> lines;
		Buffer* lineVB = nullptr;
		Buffer* gridVB = nullptr;
		Buffer* originVB = nullptr;
		UINT gridVerticeCount;
		VShader* markVS;
		PShader* markPS;
		DepthStencilState* dsState;
		BlendState* blendState;
		RasterizerState* rsState;

		float gridInterval;

		std::unordered_set<IDebug*> debugObjs;
	};
}