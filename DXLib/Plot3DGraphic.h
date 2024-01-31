#pragma once
#include "Graphic.h"
namespace DX
{
    class Plot3DGraphic :
        public Graphic
    {
    public:
        Plot3DGraphic(HWND hwnd, int msaa=1);

        void Plot(std::vector<double> x, std::vector<double> y, std::vector<double> z, int r, int g, int b);
        void Scatter(std::vector<double> x, std::vector<double> y, std::vector<double> z, int r, int g, int b);
    };
}

