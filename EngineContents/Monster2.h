#pragma once
#include "CharacterManager.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineWinImage.h>

// ���� :
class ACharacterManagerster2 : public ACharacterManager
{
public:
	// constrcuter destructer
	ACharacterManagerster2();
	~ACharacterManagerster2();

	// delete Function
	ACharacterManagerster2(const ACharacterManagerster2& _Other) = delete;
	ACharacterManagerster2(ACharacterManagerster2&& _Other) noexcept = delete;
	ACharacterManagerster2& operator=(const ACharacterManagerster2& _Other) = delete;
	ACharacterManagerster2& operator=(ACharacterManagerster2&& _Other) noexcept = delete;

	// �����͸� ����ȭ(����)
	void Serialize(UEngineSerializer& _Ser) override;
	// �����͸� ����(�Ҷ�)
	void DeSerialize(UEngineSerializer& _Ser) override;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

