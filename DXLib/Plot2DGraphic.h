#pragma once
#include "Graphic.h"

namespace DX
{
    class Plot2DGraphic :
        public Graphic
    {
    public:
        Plot2DGraphic(HWND hwnd);
        void Plot(std::vector<double> x, std::vector<double> y, int r, int g, int b);
        void Scatter(std::vector<double> x, std::vector<double> y, int r, int g, int b);
    };
}
