#pragma once
#include "Actor.h"
#include "DirectXTK/include/SpriteFont.h"

#include "DirectXTK/include/SpriteBatch.h"

namespace DX
{
    class Text :
        public Actor
    {
    public:
        Text(const Graphic* graphic);

        void SetStr(std::string str);
        void SetPos(float x, float y);
        void SetColor(float r, float g, float b);
        void SetScale(float x, float y);
        
        void Render()override;

    private:
        std::string m_str;
        float m_x;
        float m_y;
        float m_colR;
        float m_colG;
        float m_colB;
        float m_scaleX;
        float m_scaleY;

        std::unique_ptr<SpriteFont> m_spriteFont;
        std::unique_ptr<SpriteBatch> m_spriteBatch;

    };
}

