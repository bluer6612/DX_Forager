#include "PreCompile.h"
#include "PlayGameMode.h"
#include "Monster.h"
#include "Forager.h"
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
	Camera->SetActorLocation({ 0.0f, 0.0f, -750.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);

	{
		TileMapRenderer = CreateDefaultSubObject<UTileMapRenderer>();
		TileMapRenderer->SetupAttachment(RootComponent);
		TileMapRenderer->SetTileSetting(ETileMapType::Rect, "Tiles", { 56.f, 56.f }, { 56.f, 56.f }, { 0.0f, 0.0f });

		FVector ScreenPos = { -56.f * TilemapCount * 0.5f, -56.f * TilemapCount * 0.5f };
		FVector TilePos = ScreenPos;

		for (int y = 0; y < TilemapCount; y++)
		{
			for (int x = 0; x < TilemapCount; x++)
			{
				TileMapRenderer->SetTile(TilePos, 4);

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

				if (Dice < 0.85)
				{
					TileMapRenderer->SetTile(TilePos, 0);
				}
				else
				{
					TileMapRenderer->SetTile(TilePos, EngineRandom.RandomInt(1, 3));
				}

				if (x == 0 && y == 9)
				{
					TileMapRenderer->SetTile(TilePos, 14);
				}
				else if (x == 9 && y == 9)
				{
					TileMapRenderer->SetTile(TilePos, 15);
				}
				else if (x == 0 && y != 0)
				{
					TileMapRenderer->SetTile(TilePos, 8);
				}
				else if (x == 9 && y != 0)
				{
					TileMapRenderer->SetTile(TilePos, 9);
				}
				else if (y == 9)
				{
					TileMapRenderer->SetTile(TilePos, 13);
				}

				if (y == 1 && x == 9)
				{
					TileMapRenderer->SetTile(TilePos, 12);
				}
				else if (y == 1 && x >= 1)
				{
					TileMapRenderer->SetTile(TilePos, 10);
				}
				else if (y == 1 && x == 0)
				{
					TileMapRenderer->SetTile(TilePos, 11);
				}
				else if (y == 0)
				{
					TileMapRenderer->SetTile(TilePos, 5);
				}


				TilePos.X += 56.f;
			}

			TilePos.X = ScreenPos.X;
			TilePos.Y += 56.f;
		}
	}

	{
		//std::shared_ptr<class AForager> Forager = GetWorld()->SpawnActor<AForager>();
		Forager = GetWorld()->SpawnActor<AForager>();
		Forager->TileMapRenderer = TileMapRenderer;
	}
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetMainCamera();
	FVector CameraPos = Camera->GetActorLocation();
	FVector PlayerPos = Forager->GetActorLocation();
	float4 CorrectionValue = { 0, 0 };

	UEngineDebug::OutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::OutPutString("CameraPos : " + std::to_string(CameraPos.X) + "/" + std::to_string(CameraPos.Y));


	if (abs(int(PlayerPos.X) - int(CameraPos.X)) < 6)
	{
	}
	else if (int(PlayerPos.X) != int(CameraPos.X))
	{
		if (int(PlayerPos.X) - int(CameraPos.X) > 6)
		{
			CorrectionValue += { 4.f, 0.f };
		}
		else if (int(PlayerPos.X) - int(CameraPos.X) < 6)
		{
			CorrectionValue += { -4.f, 0.f };
		}
	}

	if (abs(int(PlayerPos.Y) - int(CameraPos.Y)) < 6)
	{
	}
	else if (int(PlayerPos.Y) != int(CameraPos.Y))
	{
		if (int(PlayerPos.Y) - int(CameraPos.Y) > 6)
		{
			CorrectionValue += { 0.f, 4.f };
		}
		else if (int(PlayerPos.Y) - int(CameraPos.Y) < 6)
		{
			CorrectionValue += { 0.f, -4.f };
		}
	}

	if (CorrectionValue.X != 0 || CorrectionValue.Y != 0)
	{
		Camera->SetActorLocation({ CameraPos.X + CorrectionValue.X, CameraPos.Y + CorrectionValue.Y, -750.0f, 1.f });
		Forager->SetActorLocation({ CameraPos.X + CorrectionValue.X, CameraPos.Y + CorrectionValue.Y });
	}
	else
	{
		Camera->SetActorLocation({ PlayerPos.X, PlayerPos.Y, -750.0f, 1.f });
	}
	CameraPos = Camera->GetActorLocation();

	UEngineDebug::OutPutString("CameraPos2 : " + std::to_string(CameraPos.X) + "/" + std::to_string(CameraPos.Y));
	UEngineDebug::OutPutString("PlayerPos : " + std::to_string(PlayerPos.X) + "/" + std::to_string(PlayerPos.Y));
}

void APlayGameMode::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();
}