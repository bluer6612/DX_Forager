#include "PreCompile.h"
#include "Monster2.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/TimeEventComponent.h>
#include "ForagerRenderer.h"
#include <EngineCore/Collision.h>

ACharacterManagerster2::ACharacterManagerster2()
{
	CharacterTypeValue = ECharacterType::Monster2;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// 인벤토리
	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();

	CharacterRenderer = CreateDefaultSubObject<USpriteRenderer>();
	CharacterRenderer->SetupAttachment(RootComponent);
	CharacterRenderer->SetSprite("Tevi", 0);
	CharacterRenderer->SetScale3D({ 50.0f, 50.0f });

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });

}

ACharacterManagerster2::~ACharacterManagerster2()
{
}

void ACharacterManagerster2::BeginPlay()
{
	AActor::BeginPlay();
}

void ACharacterManagerster2::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetCamera(0);

	UEngineCore::GetMainWindow().GetMousePos();

}

// 데이터를 직렬화(압축)
void ACharacterManagerster2::Serialize(UEngineSerializer& _Ser)
{
	_Ser << GetActorLocation();
}
// 데이터를 복구(할때)
void ACharacterManagerster2::DeSerialize(UEngineSerializer& _Ser)
{
	FVector Location;
	_Ser >> Location;
	SetActorLocation(Location);
}