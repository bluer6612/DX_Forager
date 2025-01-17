#include "PreCompile.h"
#include "TestGameMode.h"
#include "Monster.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/EngineCamera.h>
#include "ContentsEditorGUI.h"
#include "TestActor.h"
#include <EngineCore/EngineCore.h>
#include "PlayGameMode.h"
#include "TitleGameMode.h"
#include "TileMapGameMode.h"
#include "TitleHUD.h"

ATestGameMode::ATestGameMode()
{
	// �������� ���ּž� �մϴ�.
	// �̰� UI�����Ұ��� 
	GetWorld()->CreateCollisionProfile("Monster");
	GetWorld()->CreateCollisionProfile("Player");
	// �浹üũ �ؾ��Ѵ�.
	GetWorld()->LinkCollisionProfile("Player", "Monster");

	

	// ī�޶� �����Ÿ� �ڷ� ���� 
	// ī�޶� ��ġ������ ������ ����� �Ұ��̴�.
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({0.0f, 0.0f, -1000.0f, 1.0f});
	Camera->GetCameraComponent()->SetZSort(0, true);

	{
		std::shared_ptr<ATestActor> NewMonster = GetWorld()->SpawnActor<ATestActor>();
		NewMonster->SetActorRelativeScale3D({ 100.0f, 200.0f, 100.0f, 1.0f });
		NewMonster->SetActorLocation({ 0.0f, 0.0f, 0.0f });
	}


}

ATestGameMode::~ATestGameMode()
{

}

void ATestGameMode::Tick(float _DeltaTime)
{
	// �θ� ȣ��
	AActor::Tick(_DeltaTime);


	if (true == LoadingEnd)
	{
		// �̹����� ��ȯ 
		UEngineCore::CreateLevel<ATitleGameMode, APawn, ATitleHUD>("Titlelevel");
		UEngineCore::CreateLevel<APlayGameMode, APawn, ATitleHUD>("Playlevel");
		UEngineCore::CreateLevel<ATileMapGameMode, APawn, AHUD>("TileMapEditor");
		UEngineCore::OpenLevel("Playlevel");
	}

}

void ATestGameMode::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();

	if (false == LoadingEnd)
	{
		Thread.Start("Loading", [this]()
			{
				{
					// ���� �ȵǴ� �̴ϴ�.
					// �����尡 ����������� �� ��ü�� ����־�� �Ѵٴ� ���� ����ּ���.
					// UEngineThread Thread;

					UEngineDirectory Dir;
					if (false == Dir.MoveParentToDirectory("Resources"))
					{
						MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
						return;
					}
					Dir.Append("Image");
					std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
					for (size_t i = 0; i < ImageFiles.size(); i++)
					{
						std::string FilePath = ImageFiles[i].GetPathToString();
						UEngineTexture::Load(FilePath);
					}
				}

				{
					std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("ForagerMaterial");
					Mat->SetVertexShader("ForagerShader.fx");
					Mat->SetPixelShader("ForagerShader.fx");
				}

				{
					std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("ForagerCollisionDebugMaterial");
					Mat->SetVertexShader("EngineDebugCollisionShader.fx");
					Mat->SetPixelShader("EngineDebugCollisionShader.fx");
					// ������ ȭ�鿡 ������ ������ �̳༮�� ���� ������ ����.
					Mat->SetDepthStencilState("CollisionDebugDepth");
					Mat->SetRasterizerState("CollisionDebugRas");
				}

				UEngineSprite::CreateSpriteToMeta("Forager", ".meta");
				//UEngineSprite::CreateSpriteToMeta("img_tile_plain", ".meta");

				//DirectoryAdd("Character/Forager");
				DirectoryAdd("Water");

				this->LoadingEnd = true;
			});
	}
}

void ATestGameMode::DirectoryAdd(std::string _Append)
{
	UEngineDirectory Dir;
	Dir.MoveParentToDirectory("Resources//Image//");
	Dir.Append(_Append);
	UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
}