#pragma once
#include "CharacterManager.h"
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

	std::shared_ptr<class UTileMapRenderer> TileMapRenderer;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	//std::shared_ptr<class UTileManager> TileManager;

private:
	std::shared_ptr<class USpriteRenderer> PickaxRenderer;
	//class UTileMapRenderer* TileManager;
	//class APlayGameMode* PlayGameMode;
};