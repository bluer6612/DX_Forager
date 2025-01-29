#pragma once
#include <EngineCore/GameMode.h>
#include <EngineCore/SpriteRenderer.h>

// Ό³Έν :
class APlayGameMode : public AGameMode
{
public:
	// constrcuter destructer
	APlayGameMode();
	~APlayGameMode();

	// delete Function
	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);

	std::shared_ptr<class UTileMapRenderer> GetTileMapRenderer()
	{
		return TileManager;
	}

	void SetPlayGameMode(std::shared_ptr<class APlayGameMode> const _PlayGameMode)
	{
		PlayGameMode = _PlayGameMode;
	}

	std::shared_ptr<class APlayGameMode> PlayGameMode;

	std::shared_ptr<class UTileMapRenderer> TileManager;

	std::shared_ptr<class AForager> Forager;
protected:
	void LevelChangeStart() override;

private:
};