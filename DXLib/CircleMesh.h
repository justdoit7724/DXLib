#pragma once
#include "Mesh.h"

namespace DX
{
    class DXLIB_DLL CircleMesh :
        public Mesh
    {
    public:
        CircleMesh(ID3D11Device* device, int sCount);
    };
}
