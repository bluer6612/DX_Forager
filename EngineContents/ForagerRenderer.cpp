#include "PreCompile.h"
#include "ForagerRenderer.h"

ForagerRenderer::ForagerRenderer()
{
	CreateRenderUnit();
	SetMesh("Rect");
	SetMaterial("MyMaterial");

	MyColor.Albedo = float4(1.0f, 1.0f, 1.0f, 1.0f);

	GetRenderUnit().ConstantBufferLinkData("FMyColor", MyColor);
}

ForagerRenderer::~ForagerRenderer()
{
}

