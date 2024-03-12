#include "ShaderVertex.cginc"


struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD1;
};

VS_OUTPUT main(STD_VS_INPUT input)
{
    VS_OUTPUT output;
    output.pos = float4(input.pos,0);
    output.tex = input.tex;

	return output;
}