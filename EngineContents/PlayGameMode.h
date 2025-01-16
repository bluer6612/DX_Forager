#pragma once
#include <EngineCore/GameMode.h>

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


protected:
	void LevelChangeStart() override;

private:
	std::shared_ptr<class AForager> Forager;
	std::shared_ptr<class ATileManager> TileManager;
};