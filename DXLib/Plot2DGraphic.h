#pragma once
#include "Graphic.h"

namespace DX
{
    class Object;
    class Text;

    class DXLIB_DLL Plot2DGraphic :
        public Graphic
    {
    public:
        Plot2DGraphic(HWND hwnd);
        ~Plot2DGraphic()override;
        void Plot(std::vector<DirectX::XMFLOAT2> pt, DirectX::XMFLOAT3 color);
        void Scatter(std::vector<DirectX::XMFLOAT2> pt, std::vector<float> rads, std::vector<DirectX::XMFLOAT3> colors);
        void Clear();
        void ClearPlot();
        void ClearScatter();
        void ClearAxis();


        void UpdateCamMovement(float spf) override;


    private:
        Object* m_axis;
        Object* m_plotQuad;

        std::vector<Text*> m_axisHorUnits;
        std::vector<Text*> m_axisVerUnits;
    };
}
