#pragma once
#include <EngineCore/Renderer.h>

struct FMyColor
{
	float4 Albedo;
};

// Ό³Έν :
class ForagerRenderer : public URenderer
{
public:
	// constrcuter destructer
	ForagerRenderer();
	~ForagerRenderer();

	// delete Function
	ForagerRenderer(const ForagerRenderer& _Other) = delete;
	ForagerRenderer(ForagerRenderer&& _Other) noexcept = delete;
	ForagerRenderer& operator=(const ForagerRenderer& _Other) = delete;
	ForagerRenderer& operator=(ForagerRenderer&& _Other) noexcept = delete;

protected:

private:
	FMyColor MyColor;
};

