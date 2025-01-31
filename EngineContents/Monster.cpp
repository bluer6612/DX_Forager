#include "PreCompile.h"
#include "Monster.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/TimeEventComponent.h>
#include "ForagerRenderer.h"
#include <EngineCore/Collision.h>
#include "MyGameInstance.h"

AMonster::AMonster()
{
	CharacterTypeValue = ECharacterType::Monster;
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// �κ��丮
	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();

	CharacterRenderer = CreateDefaultSubObject<USpriteRenderer>();
	CharacterRenderer->SetupAttachment(RootComponent);
	CharacterRenderer->SetTexture("skullidle.bmp");
	CharacterRenderer->SetScale3D({ 50.0f, 50.0f });

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });

}

AMonster::~AMonster()
{
}

void AMonster::BeginPlay()
{
	AActor::BeginPlay();
}

void AMonster::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetCamera(0);

	UEngineCore::GetMainWindow().GetMousePos();



	//if (���� �����϶���)
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

void AMonster::Serialize(UEngineSerializer& _Ser)
{
	_Ser << GetActorLocation();
	//_Ser << std::string("Test.png");
	//_Ser << FVector(50.0f, 50.0f);
}


void AMonster::DeSerialize(UEngineSerializer& _Ser)
{
	FVector SavePos;
	_Ser >> SavePos;
	SetActorLocation(SavePos);

}