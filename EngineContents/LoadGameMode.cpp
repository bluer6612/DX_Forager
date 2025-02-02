#include "PreCompile.h"
#include "LoadGameMode.h"
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

ALoadGameMode::ALoadGameMode()
{
}

ALoadGameMode::~ALoadGameMode()
{
}

void ALoadGameMode::Tick(float _DeltaTime)
{
	// �θ� ȣ��
	AActor::Tick(_DeltaTime);

	if (true == ThreadLoadingInit)
	{
		if (0 == LoadingCount)
		{
			ThreadLoadingEnd = true;
		}

		if (true == ThreadLoadingEnd)
		{
			// �̹����� ��ȯ 
			UEngineSprite::CreateSpriteToMeta("Forager", ".meta");
			DirectoryAdd("Tiles");
			DirectoryAdd("Pickax");

			UEngineCore::CreateLevel<ATitleGameMode, APawn, ATitleHUD>("Titlelevel");
			UEngineCore::CreateLevel<APlayGameMode, APawn, ATitleHUD>("Playlevel");
			//UEngineCore::CreateLevel<ATileMapGameMode, APawn, AHUD>("TileMapEditor");
			UEngineCore::OpenLevel("Playlevel");
		}
	}
}

void ALoadGameMode::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();

	if (false == ThreadLoadingEnd)
	{
		Thread.Start("Loading", [this]()
			{
				{
					UEngineDirectory Dir;
					if (false == Dir.MoveParentToDirectory("Resources"))
					{
						MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
						return;
					}
					Dir.Append("Image");
					std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });

					LoadingCount = static_cast<int>(ImageFiles.size());
					 
					for (int i = 0; i < ImageFiles.size(); i++)
					{
						std::string FilePath = ImageFiles[i].GetPathToString();

						// IOCP 1000���� ���̶�� �޸𸮰� ����?
						UEngineCore::GetThreadPool().WorkQueue([this, FilePath]()
							{
								UEngineTexture::ThreadSafeLoad(FilePath);
								--(this->LoadingCount);
							});
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

				ThreadLoadingInit = true;
			});
	}
}

void ALoadGameMode::DirectoryAdd(std::string _Append, FVector _Pivot)
{
	UEngineDirectory Dir;
	Dir.MoveParentToDirectory("Resources//Image//");
	Dir.Append(_Append);
	UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString(), _Pivot);
}