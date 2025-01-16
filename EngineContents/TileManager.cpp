#include "PreCompile.h"
#include "TileManager.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/CameraActor.h>

ATileManager::ATileManager()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	PivotSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	PivotSpriteRenderer->SetupAttachment(RootComponent);
	PivotSpriteRenderer->SetRelativeScale3D({ 50.0f, 50.0f, 1.0f });

	GroundTileMap = CreateDefaultSubObject<UTileMapRenderer>();
	GroundTileMap->SetupAttachment(RootComponent);
	GroundTileMap->SetTileSetting(ETileMapType::Rect, "Water", { 56.f, 56.f }, { 56.f, 56.f }, { 0.0f, 0.0f });

	CroppatchTile = CreateDefaultSubObject<UTileMapRenderer>();
	CroppatchTile->SetupAttachment(RootComponent);
	//CroppatchTile->SetTileSetting(ETileMapType::Rect, "Water", { 56.f, 56.f }, { 56.f, 56.f }, { 0.0f, 0.0f });
}

ATileManager::~ATileManager()
{
}

void ATileManager::BeginPlay()
{
	AActor::BeginPlay();

	//건물 타일
	{
		FVector ScreenPos = {0.0f, 0.0f, 0.0f};

		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				GroundTileMap->SetTile(ScreenPos, 0);
			}
		}
	}

	////농사 타일
	//{
	//	FVector2D Location = { static_cast<float>(0), static_cast<float>(ScreenHY - 32 - 16 + 8) };
	//	FVector2D Location2 = { static_cast<float>(17), static_cast<float>(ScreenHY - 32 - 16 + 25 ) };
	//	FVector2D StartPos = Location2;

	//	CroppatchTile = GetWorld()->SpawnActor<ATileMap>();
	//	CroppatchTile->SetActorLocation(Location);
	//	CroppatchTile->Create("EmptyTile.png", { 56, 8 }, { 34, 34 });

	//	int Index = 0;

	//	for (int y = 0; y < 8; ++y)
	//	{
	//		for (int x = 0; x < 56; ++x)
	//		{
	//			CroppatchTile->SetTileSpriteIndex({ x, y }, { 1, 1 }, { 33, 33 }, 0, Index, ERenderOrder::BUILDINGUP);

	//			if ((y >= 4 && y <= 7) && (x >= 21 && x <= 24))
	//			{				
	//				CroppatchTile->GetTileByLocation(StartPos)->SetCropsIndex(-1);
	//			}
	//			else
	//			{
	//				CroppatchTile->GetTileByLocation(StartPos)->SetCropsIndex(-2);
	//			}
	//			CroppatchTile->GetTileByLocation(StartPos)->SetLocation(StartPos);

	//			CroppatchTileImage[Index] = CreateDefaultSubObject<USpriteRenderer>();
	//			CroppatchTileImage[Index]->SetComponentCrate(CroppatchTileImage[Index], "EmptyTile.png", { 34, 34 }, { StartPos }, ERenderOrder::BUILDINGTILE);
	//			CroppatchTileImage[Index]->SetPivotType(PivotType::Bot);
	//			CroppatchTileImage[Index]->SetComponentScale({33.f, 33.f});
	//			CroppatchTileImage[Index]->SetAlphafloat(0.75f);
	//			CroppatchTileImage[Index]->SetActive(false);

	//			StartPos.X += 34;
	//			++Index;
	//		}

	//		StartPos.X = Location2.X;
	//		StartPos.Y += 34;
	//	}
	//}
}

void ATileManager::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	/*std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetCamera(0);*/
	FVector MousePos = GetWorld()->GetCamera(0)->ScreenMousePosToWorldPos();
}