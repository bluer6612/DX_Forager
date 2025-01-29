#pragma once
#include "CharacterManager.h"
#include "PlayGameMode.h"
#include <EngineCore/TileMapRenderer.h>

// ���� :
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

	void SetPlayGameMode(std::shared_ptr<class APlayGameMode> const _PlayGameMode)
	{
		PlayGameMode = _PlayGameMode;
	}

	std::shared_ptr<APlayGameMode> PlayGameMode;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	//std::shared_ptr<class UTileManager> TileManager;

private:
	//class UTileMapRenderer* TileManager;
	//class APlayGameMode* PlayGameMode;
};