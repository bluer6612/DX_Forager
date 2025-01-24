#pragma once
#include <EngineCore/GameMode.h>
#include <EngineCore/SpriteRenderer.h>

// ���� :
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

protected:
	void LevelChangeStart() override;

	std::shared_ptr<class UTileMapRenderer> TileManager;

private:
	std::shared_ptr<class AForager> Forager;
};