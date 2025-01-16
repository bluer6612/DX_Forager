#include "PreCompile.h"
#include "EngineVertex.h"

// EngineCore에 있는 녀석을 가져와라
UEngineInputLayOutInfo FEngineVertex::Info;

UEngineInputLayOutInfo& FEngineVertex::GetInfo()
{
	return Info;
}

class EngineVertexInit
{
public:
	EngineVertexInit()
	{
		FEngineVertex::Info.AddInputLayout("POSITION", DXGI_FORMAT_R32G32B32A32_FLOAT);
		FEngineVertex::Info.AddInputLayout("TEXCOORD", DXGI_FORMAT_R32G32B32A32_FLOAT);
		FEngineVertex::Info.AddInputLayout("COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
	}
};

EngineVertexInit InitObject;