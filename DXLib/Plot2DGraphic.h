#pragma once
#include "Graphic.h"

namespace DX
{
    class Object;

    class DXLIB_DLL Plot2DGraphic :
        public Graphic
    {
    public:
        Plot2DGraphic(HWND hwnd);
        ~Plot2DGraphic()override;


        void Update(float spf)override;

        void Plot(std::vector<DirectX::XMFLOAT2> pt, DirectX::XMFLOAT4 color, float thick, bool isContinuous);
        void Scatter(std::vector<DirectX::XMFLOAT2> pt, std::vector<float> rads, std::vector<DirectX::XMFLOAT4> colors);
        void Surface(std::vector<std::vector<float>> x, std::vector<std::vector<float>> y, std::vector<std::vector<float>> v, float colRangeBegin, float colRangeEnd);
        void Surface(std::vector<std::vector<float>> x, std::vector<std::vector<float>> y, std::vector<std::vector<DirectX::XMFLOAT4>> v);
        void Clear();
        void ClearPlot();
        void ClearScatter();
        void ClearSurface();

        DirectX::XMFLOAT2 GetOrigin();
        DirectX::XMFLOAT2 GetPlotSize();


    private:
        void UpdateCamMovement(float spf) override;
        void UpdatePlot();

        Object* m_axis;
        Object* m_plotQuad;

        std::vector<std::vector<DirectX::XMFLOAT2>> m_scatterPts;
        std::vector<std::vector<float>> m_scatterRads;
        std::vector<std::vector<DirectX::XMFLOAT4>> m_scatterCols;
        std::vector<Object*> m_scatterObjs;

        std::vector<std::vector<DirectX::XMFLOAT2>> m_linesPos;
        std::vector<float> m_linesThick;
        std::vector<DirectX::XMFLOAT4> m_linesCol;
        std::vector<bool> m_linesContinuous;
        std::vector<Object*> m_linesObj;


        std::vector<std::vector<float>> m_surfaceX;
        std::vector<std::vector<float>> m_surfaceY;
        std::vector<std::vector<DirectX::XMFLOAT4>> m_surfaceCol;
        Object* m_surfaceObj;

        D3D11_VIEWPORT m_plotVP;
    };
}
