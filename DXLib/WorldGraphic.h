#pragma once
#include "Graphic.h"

namespace DX
{
    class DXLIB_DLL WorldGraphic :
        public Graphic
    {
    public:
        WorldGraphic(HWND hwnd, int msaa = 1);
    };
}

