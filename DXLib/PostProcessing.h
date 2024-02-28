#pragma once


namespace DX
{
	class VShader;
	class PShader;
	class Mesh;
	class BlendState;
	class DepthStencilState;
	class RasterizerState;
	class Graphic;

	class PostProcessing
	{
	public:
		PostProcessing(ID3D11Device* device, std::string psPath);
		~PostProcessing();

		void Render(const Graphic* graphic, ID3D11RenderTargetView* rtv=nullptr);

	private:

		VShader* m_vs;
		PShader* m_ps;
		Mesh* m_screenMesh;

		BlendState* m_blendState;
		DepthStencilState* m_dsState;
		RasterizerState* m_rState;
	};
}

