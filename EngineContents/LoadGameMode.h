#pragma once
#include <EngineCore/GameMode.h>
#include <atomic>
#include <EnginePlatform/EngineThread.h>

// Ό³Έν :
class ALoadGameMode : public AGameMode
{
public:
	// constrcuter destructer
	ALoadGameMode();
	~ALoadGameMode();

	// delete Function
	ALoadGameMode(const ALoadGameMode& _Other) = delete;
	ALoadGameMode(ALoadGameMode&& _Other) noexcept = delete;
	ALoadGameMode& operator=(const ALoadGameMode& _Other) = delete;
	ALoadGameMode& operator=(ALoadGameMode&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);


protected:
	void LevelChangeStart() override;

private:
	void DirectoryAdd(std::string _Append);

	std::atomic<int> LoadingCount = 0;

	std::atomic<bool> ThreadLoadingEnd = false;

	std::atomic<bool> ThreadLoadingInit = false;

	UEngineThread Thread;
};