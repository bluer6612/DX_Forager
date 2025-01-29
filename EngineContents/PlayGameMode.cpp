#include "PreCompile.h"
#include "PlayGameMode.h"
#include "Monster.h"
#include "Forager.h"
#include "TileManager.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include "ContentsEditorGUI.h"
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineRandom.h>

APlayGameMode::APlayGameMode()
{
	GetWorld()->CreateCollisionProfile("Monster");
	GetWorld()->CreateCollisionProfile("Forager");
	GetWorld()->LinkCollisionProfile("Forager", "Monster");

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);

	//UI Manager
	{
		this->SetPlayGameMode(PlayGameMode);
	}

	{
		std::shared_ptr<class AForager> Forager = GetWorld()->SpawnActor<AForager>();
		Forager->SetPlayGameMode(PlayGameMode);
	}

	{
		TileManager = CreateDefaultSubObject<UTileMapRenderer>();
		TileManager->SetupAttachment(RootComponent);
		TileManager->SetTileSetting(ETileMapType::Rect, "Tiles", { 56.f, 56.f }, { 56.f, 56.f }, { 0.0f, 0.0f });

		FVector ScreenPos = { -56.f * TilemapCount * 0.5f, -56.f * TilemapCount * 0.5f };
		FVector TilePos = ScreenPos;

		for (int y = 0; y < TilemapCount; y++)
		{
			for (int x = 0; x < TilemapCount; x++)
			{
				TileManager->SetTile(TilePos, 4);

				TilePos.X += 56.f;
			}

			TilePos.X = ScreenPos.X;
			TilePos.Y += 56.f;
		}
	}

	{
		UEngineRandom EngineRandom;
		FVector ScreenPos = { -56.f * 12 * 0.5f, -56.f * 11 * 0.5f};
		FVector TilePos = ScreenPos;
		float Dice = 0;
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				Dice = EngineRandom.Randomfloat(0.f, 1.f);

				if (Dice < 0.9)
				{
					TileManager->SetTile(TilePos, 0);
				}
				else
				{
					TileManager->SetTile(TilePos, EngineRandom.RandomInt(1, 3));
				}

				if (x == 0 && y == 9)
				{
					TileManager->SetTile(TilePos, 14);
				}
				else if (x == 9 && y == 9)
				{
					TileManager->SetTile(TilePos, 15);
				}
				else if (x == 0 && y != 0)
				{
					TileManager->SetTile(TilePos, 8);
				}
				else if (x == 9 && y != 0)
				{
					TileManager->SetTile(TilePos, 9);
				}
				else if (y == 9)
				{
					TileManager->SetTile(TilePos, 13);
				}

				if (y == 1 && x == 9)
				{
					TileManager->SetTile(TilePos, 12);
				}
				else if (y == 1 && x >= 1)
				{
					TileManager->SetTile(TilePos, 10);
				}
				else if (y == 1 && x == 0)
				{
					TileManager->SetTile(TilePos, 11);
				}
				else if (y == 0)
				{
					TileManager->SetTile(TilePos, 5);
				}


				TilePos.X += 56.f;
			}

			TilePos.X = ScreenPos.X;
			TilePos.Y += 56.f;
		}
	}
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

void APlayGameMode::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();
}