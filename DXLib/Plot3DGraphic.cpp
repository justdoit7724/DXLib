#include "pch.h"
#include "Plot3DGraphic.h"

using namespace DX;


DX::Plot3DGraphic::Plot3DGraphic(HWND hwnd, int msaa)
	:Graphic(hwnd,msaa)
{
}

void DX::Plot3DGraphic::Plot(std::vector<double> x, std::vector<double> y, std::vector<double> z, int r, int g, int b)
{
}

void DX::Plot3DGraphic::Scatter(std::vector<double> x, std::vector<double> y, std::vector<double> z, int r, int g, int b)
{
}
