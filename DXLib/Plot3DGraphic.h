#pragma once
#include "Graphic.h"

namespace DX
{
    class Object;

    class DXLIB_DLL Plot3DGraphic :
        public Graphic
    {
    public:
        Plot3DGraphic(HWND hwnd, int msaa=1);
        virtual ~Plot3DGraphic();

        void Update(float spf) override;

        void Plot(std::vector<DirectX::XMFLOAT3> pt, DirectX::XMFLOAT4 color);
        std::vector<Object*> Scatter(std::vector<DirectX::XMFLOAT3> pt, std::vector<float> rads, std::vector<DirectX::XMFLOAT4> colors);
        std::vector<Object*> Scatter(std::vector<DirectX::XMFLOAT3> pt, float rad, DirectX::XMFLOAT4 color);
        void Surface(std::vector<std::vector<float>> x1, std::vector<std::vector<float>> x2, std::vector<std::vector<float>> v, float colRangeBegin, float colRangeEnd);
        void ClearScatters();   
        void ClearSurface();
        void ClearLines();
        void ClearAxis();
        void Clear();
        DirectX::XMFLOAT3 WPos2PlotPos(DirectX::XMFLOAT3 actPos);

        DirectX::XMFLOAT3 GetOrigin();
        DirectX::XMFLOAT3 GetPlotSize();

    private:
        void UpdateCamMovement(float spf)override;
        void UpdatePlot();


        Object* m_axisPX;
        Object* m_axisNX;
        Object* m_axisPZ;
        Object* m_axisNZ;
        Object* m_axisB;

        DirectX::XMFLOAT3 m_wOrigin;
        DirectX::XMFLOAT3 m_wSize;

        std::vector<DirectX::XMFLOAT3> m_scattersPt;
        std::vector<float> m_scattersRad;
        std::vector<DirectX::XMFLOAT4> m_scattersCol;
        std::vector<Object*> m_scattersObj;

        std::vector<std::vector<float>> m_surfaceX1;
        std::vector<std::vector<float>> m_surfaceX2;
        std::vector<std::vector<float>> m_surfaceV;
        DirectX::XMFLOAT2 m_surfaceColRange;
        Object* m_surfaceObj;

        std::vector<std::vector<DirectX::XMFLOAT3>> m_linesPos;
        std::vector<DirectX::XMFLOAT4> m_linesCol;
        std::vector<Object*> m_linesObj;


    };
}

