#pragma once
#include <EngineCore/Actor.h>

// ���� :
class AForager : public AActor
{
public:
	// constrcuter destructer
	AForager();
	~AForager();

	// delete Function
	AForager(const AForager& _Other) = delete;
	AForager(AForager&& _Other) noexcept = delete;
	AForager& operator=(const AForager& _Other) = delete;
	AForager& operator=(AForager&& _Other) noexcept = delete;

protected:

private:

};

