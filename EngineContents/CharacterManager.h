#pragma once
#include <EngineCore/Actor.h>

enum ECharacterType
{
	Monster,
	Monster2,
};

// Ό³Έν :
class ACharacterManager : public AActor
{
public:
	// constrcuter destructer
	ACharacterManager();
	~ACharacterManager();

	// delete Function
	ACharacterManager(const ACharacterManager& _Other) = delete;
	ACharacterManager(ACharacterManager&& _Other) noexcept = delete;
	ACharacterManager& operator=(const ACharacterManager& _Other) = delete;
	ACharacterManager& operator=(ACharacterManager&& _Other) noexcept = delete;

	ECharacterType CharacterTypeValue;

protected:

private:
};

