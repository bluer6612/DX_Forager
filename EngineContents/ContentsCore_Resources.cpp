#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineGraphicDevice.h>
#include <EngineCore/EngineVertex.h>
#include <EngineCore/EngineIndexBuffer.h>
#include <EngineCore/Mesh.h>
#include <EngineCore/EngineBlend.h>
#include <EngineCore/EngineShader.h>
#include <EngineCore/EngineMaterial.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>



void UContentsCore::ResourcesSetting()
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
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
	}

	{
		UEngineDirectory CurDir;
		CurDir.MoveParentToDirectory("ContentsShader");

		std::vector<UEngineFile> ShaderFiles = CurDir.GetAllFile(true, { ".fx", ".hlsl" });

		for (size_t i = 0; i < ShaderFiles.size(); i++)
		{
			UEngineShader::ReflectionCompile(ShaderFiles[i]);
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

	/*UEngineSprite::CreateSpriteToMeta("Player.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("TileMap.png", ".sdata");*/

	DirectoryAdd("Character/Forager");
	DirectoryAdd("Tiles");
}

void UContentsCore::DirectoryAdd(std::string _Append)
{
	UEngineDirectory Dir;
	Dir.MoveParentToDirectory("Resources//Image//");
	Dir.Append(_Append);
	UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
}