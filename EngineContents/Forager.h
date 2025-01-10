#pragma once
#include "CharacterManager.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineWinImage.h>

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

	std::shared_ptr<class USpriteRenderer> GetRenderer()
	{
		return Renderer;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;


	std::shared_ptr<class USpriteRenderer> Renderer;

	std::shared_ptr<class UCollision> Collision;

};

