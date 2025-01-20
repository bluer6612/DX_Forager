#include "PreCompile.h"
#include "Forager.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/TimeEventComponent.h>
#include <EngineCore/Collision.h>
#include "ForagerRenderer.h"
#include "MyGameInstance.h"

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

	GetWorld()->GetMainCamera()->AttachToActor(this);

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
	FVector ActorPos = GetActorLocation();

	int ChangeAnimation = 0;
	if (MousePos.X < ActorPos.X) 
	{
		Dir = "Left";
		ChangeAnimation = 1;
	}
	else if (MousePos.X > ActorPos.X)
	{
		Dir = "Right";
		ChangeAnimation = 1;
	}

	if (UEngineInput::IsPress('W'))
	{
		AddRelativeLocation(FVector{ 0.0f, 400.0f * _DeltaTime, 0.0f });
 		ChangeAnimation = 2;
		ActorPos;
	}

	if (UEngineInput::IsPress('S'))
	{
		AddRelativeLocation(FVector{ 0.0f, -400.0f * _DeltaTime, 0.0f });
		ChangeAnimation = 2;
	}
	if (UEngineInput::IsPress('A'))
	{
		AddRelativeLocation(FVector{ -400.0f * _DeltaTime, 0.0f, 0.0f });
		ChangeAnimation = 2;
	}
	if (UEngineInput::IsPress('D'))
	{
		AddRelativeLocation(FVector{ 400.0f * _DeltaTime, 0.0f, 0.0f });
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
		}
	}
	

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