#pragma once
#include "EngineResources.h"
#include "EngineDeviceBuffer.h"
#include "EngineEnums.h"

// 타일맵이 2개라고 합니다.
// 300바이트짜리 100개 짜리 타일맵이 있고
// 300바이트짜리 80개 짜리 타일맵이 있다.


// 설명 :
class UEngineStructuredBuffer
{
public:
	// constrcuter destructer
	UEngineStructuredBuffer();
	~UEngineStructuredBuffer();

	// delete Function
	UEngineStructuredBuffer(const UEngineStructuredBuffer& _Other) = delete;
	UEngineStructuredBuffer(UEngineStructuredBuffer&& _Other) noexcept = delete;
	UEngineStructuredBuffer& operator=(const UEngineStructuredBuffer& _Other) = delete;
	UEngineStructuredBuffer& operator=(UEngineStructuredBuffer&& _Other) noexcept = delete;

protected:

private:
	//              데이터 하나의 크기
	//              데이터의 개수 Back
	// std::map<key, value, std::less> 
	/*static std::map<int, std::map<int, std::map<std::string, std::shared_ptr<UEngineConstantBuffer>>>> BufferMap;*/
};

