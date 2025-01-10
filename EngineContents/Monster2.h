#pragma once
#include "CharacterManager.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineWinImage.h>

// 설명 :
class AMonster2 : public ACharacterManager
{
public:
	// constrcuter destructer
	AMonster2();
	~AMonster2();

	// delete Function
	AMonster2(const AMonster2& _Other) = delete;
	AMonster2(AMonster2&& _Other) noexcept = delete;
	AMonster2& operator=(const AMonster2& _Other) = delete;
	AMonster2& operator=(AMonster2&& _Other) noexcept = delete;

	// 데이터를 직렬화(압축)
	void Serialize(UEngineSerializer& _Ser) override;
	// 데이터를 복구(할때)
	void DeSerialize(UEngineSerializer& _Ser) override;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

