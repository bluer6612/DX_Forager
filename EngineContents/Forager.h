#pragma once
#include "CharacterManager.h"
#include "PlayGameMode.h"
#include <EngineCore/TileMapRenderer.h>

// Ό³Έν :
class AForager : public ACharacterManager
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
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	std::shared_ptr<class APlayGameMode> PlayGameMode;

	class UTileMapRenderer* TileMapRenderer;

private:
};