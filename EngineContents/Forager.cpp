#include "PreCompile.h"
#include "Forager.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/TimeEventComponent.h>
#include <EngineCore/Collision.h>
#include "ForagerRenderer.h"

AForager::AForager()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// 인벤토리
	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();

	CharacterRenderer = CreateDefaultSubObject<USpriteRenderer>();
	CharacterRenderer->SetupAttachment(RootComponent);
	CharacterRenderer->SetSprite("Forager", 0);
	CharacterRenderer->BillboardOn();

	CharacterRenderer->CreateAnimation("Idle", "Forager", 4, 6, 0.25f);

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Forager");
	Collision->SetScale3D({});

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

	// GetWorld()->GetMainCamera()->AttachToActor(this);

}

AForager::~AForager()
{
}

void AForager::BeginPlay()
{
	AActor::BeginPlay();

	CharacterRenderer->ChangeAnimation("Idle");
}

void AForager::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	FVector MousePos = UEngineCore::GetMainWindow().GetMousePos();

	if (UEngineInput::IsPress('A'))
	{
		AddRelativeLocation(FVector{ -100.0f * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('D'))
	{
		AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f });
	}

	

	//if (공격 상태일때만)
	//{
	//	std::vector<UCollision*> Result;
	//	if (true == Collision->CollisionCheck("Monster", Result))
	//	{
	//		Result[0]->GetActor()->Destroy();
	//	}
	//}


	FVector Test = GetActorForwardVector();

	if (UEngineInput::IsPress('W'))
	{
		AddRelativeLocation(FVector{ 0.0f, 100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('S'))
	{
		AddRelativeLocation(FVector{ 0.0f, -100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('Q'))
	{
		AddActorRotation(FVector{ 0.0f, 0.0f , 360.0f * _DeltaTime });
	}

	if (UEngineInput::IsPress('F'))
	{
	}

	if (UEngineInput::IsPress('E'))
	{
	}

	if (UEngineInput::IsPress('R'))
	{
	}
}