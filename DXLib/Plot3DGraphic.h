#pragma once
#include "Graphic.h"
#include <DirectXMath.h>

namespace DX
{
    class Object;

    class DXLIB_DLL Plot3DGraphic :
        public Graphic
    {
    public:
        Plot3DGraphic(HWND hwnd, int msaa=1);

        void Plot(std::vector<double> x, std::vector<double> y, std::vector<double> z, int r, int g, int b);
        void Scatter(std::vector<DirectX::XMFLOAT3> pt, std::vector<float> rads, std::vector<DirectX::XMFLOAT4> colors);
        void ClearScatter();
        void ClearPlot();

    private:
        void UpdateCamMovement(float spf)override;

        Object* m_axisPX;
        Object* m_axisNX;
        Object* m_axisPZ;
        Object* m_axisNZ;
        Object* m_axisB;

        Actor* test;

        std::vector<Object*> m_scatters;
    };
}

