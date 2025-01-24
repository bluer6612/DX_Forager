#include "Transform.hlsli"

struct EngineVertex
{
	float4 POSITION : POSITION;
};

// 버텍스 쉐이더는 무조건 리턴값이 있어야 합니다.
// 인풋어셈블러2로 넘길 값을 리턴해줘야하는데.
// 이때도 규칙이 있습니다.

struct VertexShaderOutPut
{
	float4 SVPOSITION : SV_POSITION; // 뷰포트행렬이 곱해지는 포지션입니다.
};

VertexShaderOutPut Debug_VS(EngineVertex _Vertex)
{
	VertexShaderOutPut OutPut;
	OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
	return OutPut;
}


// ex) 픽셀쉐이더에서는 0번 을 쓸수 있다.
cbuffer OutColor : register(b0)
{
	float4 Color;
};

// 이미지를 샘플링해서 이미지를 보이게 만들고
float4 PixelToWorld_PS(VertexShaderOutPut _Vertex) : SV_Target0
{
	return Color;
};
