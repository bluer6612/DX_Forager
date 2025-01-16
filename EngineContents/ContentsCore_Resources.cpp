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



void UContentsCore::ResourcesSetting() {

	int Count = 24;
	{
		std::vector<FEngineVertex> Vertexs = {
			FEngineVertex{ FVector(0.0f, 0.7f, 0.0f), {0.0f , 0.0f },  {1.0f, 0.0f, 0.0f, 1.f} }, //빨강
			FEngineVertex{ FVector(-0.5f, 0.0f, 0.0f), {0.0f , 1.0f } , {1.0f, 0.0f, 0.0f, 1.f} },
			FEngineVertex{ FVector(0.0f, 0.0f, -0.5f), {0.0f , 1.0f } , {1.0f, 0.0f, 0.0f, 1.f} },

			FEngineVertex{ FVector(0.0f, 0.7f, 0.0f), {0.0f , 0.0f },  {1.0f, 0.0f, 1.0f, 1.0f} }, //마젠타
			FEngineVertex{ FVector(0.5f, 0.0f, 0.0f), {0.0f , 1.0f } , {1.0f, 0.0f, 1.0f, 1.0f}},
			FEngineVertex{ FVector(0.0f, 0.0f, -0.5f), {0.0f , 1.0f } , {1.0f, 0.0f, 1.0f, 1.0f} },

			FEngineVertex{ FVector(0.0f, 0.7f, 0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 0.0f, 1.f} }, //뒷면 빨강
			FEngineVertex{ FVector(-0.5f, 0.0f, 0.0f), {0.0f , 1.0f }, {1.0f, 0.0f, 0.0f, 1.f}},
			FEngineVertex{ FVector(0.0f, 0.0f, 0.5f), {0.0f , 1.0f } , {1.0f, 0.0f, 0.0f, 1.f}},

			FEngineVertex{ FVector(0.0f, 0.7f, 0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 1.0f, 1.0f} }, //뒷면 마젠타
			FEngineVertex{ FVector(0.5f, 0.0f, 0.0f), {0.0f , 1.0f } ,{1.0f, 0.0f, 1.0f, 1.0f}},
			FEngineVertex{ FVector(0.0f, 0.0f, 0.5f), {0.0f , 1.0f } , {1.0f, 0.0f, 1.0f, 1.0f} },

			FEngineVertex{ FVector(0.0f, -0.7f, 0.0f), {0.0f , 0.0f }, {1.0f, 1.0f, 0.0f, 1.0f} }, //앞면 노랑
			FEngineVertex{ FVector(-0.5f, 0.0f, 0.0f), {0.0f , 1.0f } , {1.0f, 1.0f, 0.0f, 1.0f} },
			FEngineVertex{ FVector(0.0f, 0.0f, -0.5f), {0.0f , 1.0f } , {1.0f, 1.0f, 0.0f, 1.0f} },

			FEngineVertex{ FVector(0.0f, -0.7f, 0.0f), {0.0f , 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f}},
			FEngineVertex{ FVector(0.5f, 0.0f, 0.0f), {0.0f , 1.0f } ,  {0.0f, 1.0f, 0.0f, 1.0f}},
			FEngineVertex{ FVector(0.0f, 0.0f, -0.5f), {0.0f , 1.0f } , {0.0f, 1.0f, 0.0f, 1.0f}},

			FEngineVertex{ FVector(0.0f, -0.7f, 0.0f), {0.0f , 0.0f }, {1.0f, 1.0f, 0.0f, 1.0f} }, //
			FEngineVertex{ FVector(-0.5f, 0.0f, 0.0f), {0.0f , 1.0f } , {1.0f, 1.0f, 0.0f, 1.0f} },
			FEngineVertex{ FVector(0.0f, 0.0f, 0.5f), {0.0f , 1.0f } ,  {1.0f, 1.0f, 0.0f, 1.0f}},

			FEngineVertex{ FVector(0.0f, -0.7f, 0.0f), {0.0f , 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },
			FEngineVertex{ FVector(0.5f, 0.0f, 0.0f), {0.0f , 1.0f } ,  {0.0f, 1.0f, 0.0f, 1.0f} },
			FEngineVertex{ FVector(0.0f, 0.0f, 0.5f), {0.0f , 1.0f } ,  {0.0f, 1.0f, 0.0f, 1.0f} },
		};
		UEngineVertexBuffer::Create("Test", Vertexs);
	}

	{
		std::vector<unsigned int> Indexs;

		for (size_t i = 0; i < Count; i++)
		{
			Indexs.push_back(i);
		}

		UEngineIndexBuffer::Create("Test", Indexs);
	}

	{
		UMesh::Create("Test");
	}


	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
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
		// 언제나 화면에 나오는 누구도 이녀석의 앞을 가릴수 없어.
		Mat->SetDepthStencilState("CollisionDebugDepth");
		Mat->SetRasterizerState("CollisionDebugRas");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("Test");
		Mat->SetVertexShader("TestShader2.fx");
		Mat->SetPixelShader("TestShader2.fx");
	}

	UEngineSprite::CreateSpriteToMeta("Forager", ".meta");
	//UEngineSprite::CreateSpriteToMeta("TileMap.png", ".sdata");

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