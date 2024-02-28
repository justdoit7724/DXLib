#pragma once
#include "Actor.h"
#include "DirectXTK/include/SpriteFont.h"

#include "DirectXTK/include/SpriteBatch.h"

namespace DX
{
    class DXLIB_DLL Text :
        public Actor
    {
    public:
        Text(const Graphic* graphic);

        void SetStr(std::string str);
        void SetPos(float x, float y, float z=0);
        void SetColor(float r, float g, float b);
        void SetScale(float x, float y);
        void Set3D(bool is3D);
        
        void Render()override;

    private:
        std::string m_str;
        float m_x;
        float m_y;
        float m_z;
        float m_colR;
        float m_colG;
        float m_colB;
        float m_scaleX;
        float m_scaleY;
        bool m_is3D;

        DirectX::SpriteFont* m_spriteFont;
        DirectX::SpriteBatch* m_spriteBatch;

    };
}

