#pragma once
#include "Renderer.h"
#include <EngineBase/EngineDelegate.h>
#include "SpriteRenderer.h"
#include <unordered_map>

enum ETileMapType
{
	Rect,
	Iso,
};

enum ETileMapRenderType
{
	Normal,
	Instancing,
};


struct FTileIndex
{
	union
	{
		struct
		{
			int X;
			int Y;
		};
		__int64 Key;
	};
};


struct FTileData
{
	bool IsBlock = false;
	int SpriteIndex = 0;
	FTileIndex Index;
	FResultColor ColorData;
	FSpriteData SpriteData;
};

// 설명 :
class UTileMapRenderer : public URenderer
{
public:
	class FrameAnimation
	{
	public:
		UEngineSprite* Sprite = nullptr;
		std::vector<int> FrameIndex;
		std::vector<float> FrameTime;
		std::map<int, EngineDelegate> Events;

		int CurIndex = 0;
		int ResultIndex = 0;
		float CurTime = 0.0f;
		bool Loop = true;
		bool IsEnd = false;

		void Reset()
		{
			CurIndex = 0;
			CurTime = 0;
			ResultIndex = 0;
			IsEnd = false;
		}
	};

	// constrcuter destructer
	ENGINEAPI UTileMapRenderer();
	ENGINEAPI ~UTileMapRenderer();

	// delete Function
	UTileMapRenderer(const UTileMapRenderer& _Other) = delete;
	UTileMapRenderer(UTileMapRenderer&& _Other) noexcept = delete;
	UTileMapRenderer& operator=(const UTileMapRenderer& _Other) = delete;
	UTileMapRenderer& operator=(UTileMapRenderer&& _Other) noexcept = delete;

	ENGINEAPI std::string GetCurSpriteName()
	{
		return Sprite->GetName();
	}

	// 시작할때 맵크기를 다 정하고 시작합니다.
	// 그런데 Unordered map이되면 중간에 얼마든지 크기를 기울수 있습니다.
	// ENGINEAPI void CreateTileMap(int _X, int _Y, )

	ENGINEAPI void SetTileSetting(ETileMapType _Type, std::string_view _Name, FVector _TileSize, FVector _ImageSize, FVector _Pivot);


	ENGINEAPI void SetTile(FVector _Pos, int _Spriteindex);
	ENGINEAPI void RemoveTile(FVector _Pos);

	// 없으면 만들어요.
	ENGINEAPI void SetTile(int _X, int _Y, int _Spriteindex);

	ENGINEAPI void RemoveTile(int _X, int _Y);

	ENGINEAPI class UEngineSprite* GetSprite()
	{
		return Sprite;
	}

	ENGINEAPI FTileIndex WorldPosToTileIndex(FVector _Pos);

	ENGINEAPI FVector TileIndexToWorldPos(FTileIndex _Pos);

	// 데이터를 직렬화(압축)
	ENGINEAPI void Serialize(UEngineSerializer& _Ser) override;
	// 데이터를 복구(할때)
	ENGINEAPI void DeSerialize(UEngineSerializer& _Ser) override;

protected:
	ENGINEAPI void Render(class UEngineCamera* _Camera, float _DeltaTime) override;

	ENGINEAPI void RenderNormal(class UEngineCamera* _Camera, float _DeltaTime);

	ENGINEAPI void RenderInstancing(class UEngineCamera* _Camera, float _DeltaTime);

	void BeginPlay() override;
	void ComponentTick(float _DeltaTime) override;

private:
	// 인스턴싱용 데이터 모음용 자료구조
	std::vector<FTransform> InstTransform;

	//FResultColor ColorData;//FSpriteData SpriteData;
	std::vector<FResultColor> InstColorData;

	std::vector<FSpriteData> InstSpriteData;

	bool IsAutoScale = true;
	float AutoScaleRatio = 1.0f;

	FVector TileSize;
	FVector ImageSize;
	FVector TilePivot;
	ETileMapType TileMapType = ETileMapType::Rect;
	ETileMapRenderType TileMapRenderMove = ETileMapRenderType::Normal;

	class UEngineSprite* Sprite = nullptr;
	// map보다 빠르다.
// hash 기반의 맵이다.
// 이건 꼭 이론적으로 추후에 설명해줘야 합니다.
// std::vector<std::vector> 
// 중간 확장이 될수 있다.
// 2D 이미지만 가능
	std::unordered_map<__int64, FTileData> Tiles;
};

