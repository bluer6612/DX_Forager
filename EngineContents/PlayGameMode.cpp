#include "PreCompile.h"
#include "PlayGameMode.h"
#include "Monster.h"
#include "Forager.h"
#include "TileManager.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/EngineCamera.h>
#include "ContentsEditorGUI.h"
#include <EngineBase/EngineDebug.h>

APlayGameMode::APlayGameMode()
{
	GetWorld()->CreateCollisionProfile("Monster");
	GetWorld()->CreateCollisionProfile("Forager");
	GetWorld()->LinkCollisionProfile("Forager", "Monster");

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({0.0f, 0.0f, -1000.0f, 1.0f});
	Camera->GetCameraComponent()->SetZSort(0, true);

	{
		Forager = GetWorld()->SpawnActor<AForager>();
	}

	{
		TileManager = CreateDefaultSubObject<UTileMapRenderer>();
		TileManager->SetupAttachment(RootComponent);
		TileManager->SetTileSetting(ETileMapType::Rect, "Water", { 56.f, 56.f }, { 56.f, 56.f }, { 0.0f, 0.0f });

		FVector ScreenPos = { -56.f * 10 * 0.5f, -56.f, 10 };
		FVector TilePos = ScreenPos;

		//y 14, x 24
		for (int y = 0; y < 14; y++)
		{
			for (int x = 0; x < 24; x++)
			{
				TileManager->SetTile(TilePos, 0);

				TilePos.X += 56.f;
			}

			TilePos.X = ScreenPos.X;
			TilePos.Y += 56.f;
		}

		for (int y = 0; y < 14; y++)
		{
			for (int x = 0; x < 24; x++)
			{
				TileManager->SetActive(true);
			}
		}
	}

	{
		std::shared_ptr<AMonster> NewMonster = GetWorld()->SpawnActor<AMonster>();
		NewMonster->SetActorLocation({ 300.0f, 0.0f, 0.0f });
	}
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	UEngineDebug::OutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
}

void APlayGameMode::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();
}