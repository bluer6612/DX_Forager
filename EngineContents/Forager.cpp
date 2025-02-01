#include "PreCompile.h"
#include "Forager.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/TileMapRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/TimeEventComponent.h>
#include <EngineCore/Collision.h>
#include <EngineCore/FontRenderer.h>
#include "ForagerRenderer.h"
#include "PlayGameMode.h"

AForager::AForager()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// 인벤토리
	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();

	CharacterRenderer = CreateDefaultSubObject<USpriteRenderer>();
	CharacterRenderer->SetSprite("Forager", RootComponent);
	CharacterRenderer->SetAutoScaleRatio(3.5f);
	CharacterRenderer->CreateAnimation("Idle" + std::string("Right"), "Forager", 0, 1, 0.15f);
	CharacterRenderer->CreateAnimation("Idle" + std::string("Left"), "Forager", 11, 12, 0.15f);
	CharacterRenderer->CreateAnimation("Run" + std::string("Right"), "Forager", 3, 6, 0.15f);
	CharacterRenderer->CreateAnimation("Run" + std::string("Left"), "Forager", 7, 10, 0.15f);

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Forager");
	Collision->SetScale3D({50.f, 50.f});

	Collision->SetCollisionEnter([](UCollision* _This, UCollision* _Other)
		{
			_Other->GetActor()->Destroy();
		});

	//Collision->SetCollisionStay([](UCollision* _This, UCollision* _Other)
	//	{
	//		UEngineDebug::OutPutString("Stay");
	//	});

	//Collision->SetCollisionEnd([](UCollision* _This, UCollision* _Other)
	//	{
	//		UEngineDebug::OutPutString("End");
	//	});

	//TileMapRenderer = CreateDefaultSubObject<UTileMapRenderer>();
	//TileMapRenderer->SetupAttachment(RootComponent);

	//GetWorld()->GetMainCamera()->AttachToActor(this);

}

AForager::~AForager()
{
}

void AForager::BeginPlay()
{
	AActor::BeginPlay();

	CharacterRenderer->ChangeAnimation("Run" + Dir);
}

void AForager::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetMainCamera();
	FVector MousePos = Camera->ScreenMousePosToWorldPos();
	FVector PlayerPos = GetActorLocation();
	FVector MovePos = { 0.f, 0.f, 0.f };

	UEngineDebug::OutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));

	int ChangeAnimation = 0;
	if (MousePos.X < PlayerPos.X) 
	{
		Dir = "Left";
		ChangeAnimation = 1;
	}
	else if (MousePos.X > PlayerPos.X)
	{
		Dir = "Right";
		ChangeAnimation = 1;
	}

	if (UEngineInput::IsPress('W'))
	{
		MovePos += {0.f, MoveSpeed * _DeltaTime, 0.f};
 		ChangeAnimation = 2;
	}
	if (UEngineInput::IsPress('S'))
	{
		MovePos += { 0.f, -MoveSpeed * _DeltaTime, 0.f };
		ChangeAnimation = 2;
	}
	if (UEngineInput::IsPress('A'))
	{
		MovePos += { -MoveSpeed * _DeltaTime, 0.f, 0.f };
		ChangeAnimation = 2;
	}
	if (UEngineInput::IsPress('D'))
	{
		MovePos += { MoveSpeed * _DeltaTime, 0.f, 0.f };
		ChangeAnimation = 2;
	}

	if (UEngineInput::IsFree('W') && UEngineInput::IsFree('D') && UEngineInput::IsFree('A') && UEngineInput::IsFree('S'))
	{
		ChangeAnimation = 1;
	}

	if (ChangeAnimation > 0)
	{
		if (ChangeAnimation == 1)
		{
			CharacterRenderer->ChangeAnimation("Idle" + Dir);
		}
		else if (ChangeAnimation == 2)
		{
			CharacterRenderer->ChangeAnimation("Run" + Dir);

			float4 CorrectionValue = { 0, 0 };
			if (MovePos.X < 0)
			{
				CorrectionValue += { -64.f, 0.f };
			}
			if (MovePos.Y < 0)
			{
				CorrectionValue += { 0.f, -64.f };
			}

			FTileIndex TileIndex = TileMapRenderer->WorldPosToTileIndex({GetActorLocation().X + MovePos.X + CorrectionValue.X, GetActorLocation().Y + MovePos.Y + CorrectionValue.Y});
			FTileData& Tile = TileMapRenderer->Tiles[TileIndex.Key];
			if (false == Tile.IsBlock)
			{
				AddRelativeLocation(MovePos);
			}
		}
	}

	//Camera->SetActorLocation({ PlayerPos.X, PlayerPos.Y, -1000.0f, 1.0f });
}