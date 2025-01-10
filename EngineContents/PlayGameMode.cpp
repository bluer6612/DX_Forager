#include "PreCompile.h"
#include "PlayGameMode.h"
#include "Monster.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/EngineCamera.h>
#include "ContentsEditorGUI.h"

APlayGameMode::APlayGameMode()
{
	GetWorld()->CreateCollisionProfile("Monster");
	GetWorld()->CreateCollisionProfile("Player");
	GetWorld()->LinkCollisionProfile("Player", "Monster");

	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({0.0f, 0.0f, -1000.0f, 1.0f});
	Camera->GetCameraComponent()->SetZSort(0, true);

	{
		std::shared_ptr<AMonster> NewMonster = GetWorld()->SpawnActor<AMonster>();
		NewMonster->SetActorLocation({ 300.0f, 0.0f, 0.0f });
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