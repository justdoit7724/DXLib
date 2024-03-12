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


        void Update(float spf)override;

        void Plot(std::vector<DirectX::XMFLOAT2> pt, DirectX::XMFLOAT4 color, float thick);
        void Scatter(std::vector<DirectX::XMFLOAT2> pt, std::vector<float> rads, std::vector<DirectX::XMFLOAT4> colors);
        void Clear();
        void ClearPlot();
        void ClearScatter();
        void ClearAxis();




    private:
        void UpdateCamMovement(float spf) override;
        void UpdatePlot();

        Object* m_axis;
        Object* m_plotQuad;

        std::vector<Text*> m_axisHorUnits;
        std::vector<Text*> m_axisVerUnits;

        std::vector<std::vector<DirectX::XMFLOAT2>> m_scatterPts;
        std::vector<std::vector<float>> m_scatterRads;
        std::vector<std::vector<DirectX::XMFLOAT4>> m_scatterCols;
        std::vector<Object*> m_scatterObjs;

        std::vector<std::vector<DirectX::XMFLOAT2>> m_linesPos;
        std::vector<float> m_linesThick;
        std::vector<DirectX::XMFLOAT4> m_linesCol;
        std::vector<Object*> m_linesObj;



        D3D11_VIEWPORT m_plotVP;
    };
}
