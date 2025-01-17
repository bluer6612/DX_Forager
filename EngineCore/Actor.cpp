#include "PreCompile.h"
#include "Actor.h"
#include "SceneComponent.h"

UGameInstance* AActor::GetGameInstance()
{
	return GEngine->GetGameInstance();
}

AActor::AActor()
{
}

AActor::~AActor()
{
	RootComponent = nullptr;
}

void AActor::BeginPlay()
{
	if (nullptr != RootComponent)
	{
		RootComponent->BeginPlay();
	}

	for (std::shared_ptr<class UActorComponent>& ActorComponent : ActorComponentList)
	{
		ActorComponent->BeginPlay();
	}
	
}

void AActor::Tick(float _DeltaTime)
{
	// 자기 자식들의 tick도 돌려준다.
	for (std::shared_ptr<AActor>& Actor : ChildList)
	{
		Actor->Tick(_DeltaTime);
	}

	// 엄마아빠가 내 rootcomponent의 tick들 올려줄꺼라
	// 엄마아빠가 있는 actor는 자신의 root를 컴포넌트를 돌릴필요가 벗어요.
	if (nullptr == Parent)
	{
		if (nullptr != RootComponent)
		{
			RootComponent->ComponentTick(_DeltaTime);
		}
	}
	

	for (std::shared_ptr<class UActorComponent> ActorComponent : ActorComponentList)
	{
		if (false == ActorComponent->IsActive())
		{
			continue;
		}

		ActorComponent->ComponentTick(_DeltaTime);
	}
}

void AActor::AttachToActor(AActor* _Parent)
{
	if (nullptr == RootComponent)
	{
		MSGASSERT("씬 컴포넌트가 루트가 아닌 액터가 부모를 가질수 없습니다.");
		return;
	}

	if (nullptr == _Parent->RootComponent)
	{
		MSGASSERT("씬 컴포넌트가 루트가 아닌 액터가 부모를 가질수 없습니다.");
		return;
	}

	Parent = _Parent;
	// 나는 부모님 자식으로 들어간다.
	_Parent->ChildList.push_back(GetThis<AActor>());
	RootComponent->SetupAttachment(_Parent->RootComponent);
}


FVector AActor::GetActorUpVector()
{
	if (nullptr == RootComponent)
	{
		return FVector(0.0f, 0.0f, 0.0f, 1.0f);
	}

	return RootComponent->GetTransformRef().World.GetUp();
}

FVector AActor::GetActorRightVector()
{
	if (nullptr == RootComponent)
	{
		return FVector(0.0f, 0.0f, 0.0f, 1.0f);
	}
	return RootComponent->GetTransformRef().World.GetRight();
}

FVector AActor::GetActorForwardVector()
{
	if (nullptr == RootComponent)
	{
		return FVector(0.0f, 0.0f, 0.0f, 1.0f);
	}
	return RootComponent->GetTransformRef().World.GetFoward();
}