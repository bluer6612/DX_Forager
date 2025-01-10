#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

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

protected:
	std::shared_ptr<class USpriteRenderer> GetRenderer()
	{
		return CharacterRenderer;
	}

	std::shared_ptr<class USpriteRenderer> CharacterRenderer;
	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;
	std::shared_ptr<class UCollision> Collision;

	ECharacterType CharacterTypeValue;
private:
};

