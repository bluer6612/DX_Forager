#include "PreCompile.h"
#include "Forager.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/TimeEventComponent.h>
#include <EngineCore/Collision.h>
#include <EngineCore/FontRenderer.h>
#include "ForagerRenderer.h"
#include "MyGameInstance.h"
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

	std::shared_ptr<UFontRenderer> Font = CreateDefaultSubObject<UFontRenderer>();
	Font->SetFont("궁서");
	Font->SetText("폰트 랜더러에영");
	Font->SetupAttachment(RootComponent);

	//GetWorld()->GetMainCamera()->AttachToActor(this);X
}

AForager::~AForager()
{
}

void AForager::BeginPlay()
{
	AActor::BeginPlay();

	CharacterRenderer->ChangeAnimation("Run" + Dir);

	{
		//PlayGameMode = GetWorld()->SpawnActor<APlayGameMode>();
		TileMapRenderer = PlayGameMode->GetTileMapRenderer();
	}
}

void AForager::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetMainCamera();
	FVector MousePos = Camera->ScreenMousePosToWorldPos();
	FVector PlayerPos = GetActorLocation();
	FVector MovePos = { 0.f, 0.f, 0.f };

	UEngineDebug::OutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::OutPutString("PlayerPos : " + std::to_string(PlayerPos.X) + "/" + std::to_string(PlayerPos.Y));
	UEngineDebug::OutPutString("MousePos : " + std::to_string(MousePos.X) + "/" + std::to_string(MousePos.Y));

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

			FTileIndex TileIndex = PlayGameMode->GetTileMapRenderer()->WorldPosToTileIndex({GetActorLocation().X + MovePos.X, GetActorLocation().Y + MovePos.Y});
			FTileData& Tile = PlayGameMode->GetTileMapRenderer()->Tiles[TileIndex.Key];
			if (false == Tile.IsBlock)
			{
				AddRelativeLocation(MovePos);
			}
		}
	}

	Camera->SetActorLocation({ PlayerPos.X, PlayerPos.Y, -1000.0f, 1.0f });
	

	//if (공격 상태일때만)
	//{
	//	std::vector<UCollision*> Result;
	//	if (true == Collision->CollisionCheck("Monster", Result))
	//	{
	//		Result[0]->GetActor()->Destroy();
	//	}
	//}

	if (UEngineInput::IsPress('E'))
	{
		GetGameInstance<MyGameInstance>()->InvenWidget->SetActive(false);
	}

	if (UEngineInput::IsPress('R'))
	{
		UEngineCore::GetThreadPool().WorkQueue([]()
			{
				UEngineDebug::OutPutString("Thread Work");
			});

		// GetGameInstance<MyGameInstance>()->InvenWidget->SetActive(true);
	}

	GetGameInstance<MyGameInstance>()->Status.Hp -= 1;
}