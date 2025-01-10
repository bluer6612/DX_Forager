#pragma once
#include "CharacterManager.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineWinImage.h>

// Ό³Έν :
class ACharacterManagerster : public ACharacterManager
{
public:
	// constrcuter destructer
	ACharacterManagerster();
	~ACharacterManagerster();

	// delete Function
	ACharacterManagerster(const ACharacterManagerster& _Other) = delete;
	ACharacterManagerster(ACharacterManagerster&& _Other) noexcept = delete;
	ACharacterManagerster& operator=(const ACharacterManagerster& _Other) = delete;
	ACharacterManagerster& operator=(ACharacterManagerster&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Serialize(UEngineSerializer& _Ser) override;
	void DeSerialize(UEngineSerializer& _Ser) override;

private:
};

