#include "PreCompile.h"
#include "TileMapRenderer.h"
#include "EngineCamera.h"
#include "EngineSprite.h"
#include "EngineCore/CameraActor.h"

UTileMapRenderer::UTileMapRenderer()
{
	CreateRenderUnit();
	SetMesh("Rect");
	SetMaterial("TileMap");

	//GetRenderUnit().ConstantBufferLinkData("ResultColor", ColorData);
	//GetRenderUnit().ConstantBufferLinkData("FSpriteData", SpriteData);
	//GetRenderUnit().ConstantBufferLinkData("FUVValue", UVValue);
}

UTileMapRenderer::~UTileMapRenderer()
{
}

void UTileMapRenderer::SetTileSetting(ETileMapType _Type, std::string _Name, FVector _TileSize, FVector _ImageSize, FVector _Pivot)
{
	Sprite = UEngineSprite::Find<UEngineSprite>(_Name + std::string(".png")).get();
	if (nullptr == Sprite)
	{
		Sprite = UEngineSprite::Find<UEngineSprite>(_Name).get();
	}

	TileMapType = _Type;
	TileSize = _TileSize;
	ImageSize = _ImageSize;
	TilePivot = _Pivot;
}

void UTileMapRenderer::BeginPlay()
{
	URenderer::BeginPlay();

}

FTileIndex UTileMapRenderer::WorldPosToTileIndex(FVector _Pos)
{
	FTileIndex Result = FTileIndex();
	switch (TileMapType)
	{
	case Rect:
	{
		FVector ConvertVector = _Pos /= TileSize;
		Result.X = ConvertVector.iX();
		Result.Y = ConvertVector.iY();
		break;
	}
	case Iso:
	{
		Result.X = static_cast<int>((_Pos.X / TileSize.hX() + _Pos.Y / TileSize.hY()) / 2.0f);
		Result.Y = static_cast<int>((_Pos.Y / TileSize.hY() - _Pos.X / TileSize.hX()) / 2.0f);
		break;
	}
	default:
		break;
	}

	return Result;
}

FVector UTileMapRenderer::TileIndexToWorldPos(FTileIndex _Index)
{
	FVector Result;
	switch (TileMapType)
	{
	case Rect:
		Result.X = _Index.X * TileSize.X;
		Result.Y = _Index.Y * TileSize.X;
		break;
	case Iso:
	{
		Result.X = (_Index.X - _Index.Y) * TileSize.hX();
		Result.Y = (_Index.X + _Index.Y) * TileSize.hY();
		break;
	}
	default:
		break;
	}

	return Result;
}

void UTileMapRenderer::Render(UEngineCamera* _Camera, float _DeltaTime)
{
	// URenderer::Render(_Camera, _DeltaTime);
	FTransform& CameraTrans = _Camera->GetTransformRef();
	FTransform& RendererTrans = GetTransformRef();
	//	// 랜더러는 월드 뷰 프로젝트를 다 세팅받았고
	RendererTrans.View = CameraTrans.View;
	RendererTrans.Projection = CameraTrans.Projection;
	RendererTrans.WVP = RendererTrans.World * RendererTrans.View * RendererTrans.Projection;
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();


	if (0 == Tiles.size())
	{
		return;
	}
	
	URenderUnit& Unit = GetRenderUnit();

	FTransform Trans;
	FMatrix Scale;
	FMatrix Pos;

	Scale.Scale(ImageSize);

	for (std::pair<const __int64, FTileData>& TilePair : Tiles)
	{
		FTileData& Tile = TilePair.second;
		FTileIndex Index;
		Index.Key = TilePair.first;
		FVector ConvertPos = TileIndexToWorldPos(Index);
		FVector CameraPost = Camera->GetActorLocation();

		/*if ((ConvertPos.X - CameraPost.X < -640.f - 56.f - CameraPost.X || ConvertPos.Y - CameraPost.Y < -360.f - 56.f - CameraPost.Y)
			|| (ConvertPos.X + CameraPost.X > 640.f + 56.f + CameraPost.X || ConvertPos.Y + CameraPost.Y > 360.f + 56.f + CameraPost.Y))*/
		//if (화면 바깥에 나간 타일은)
		if ((ConvertPos.X - CameraPost.X > -640.f - 56.f - CameraPost.X && ConvertPos.Y - CameraPost.Y > -360.f - 56.f - CameraPost.Y)
			|| (ConvertPos.X + CameraPost.X < 640.f + 56.f + CameraPost.X && ConvertPos.Y + CameraPost.Y < 360.f + 56.f + CameraPost.Y))
		{
			//UEngineDebug::OutPutString("CameraPos : " + std::to_string(ConvertPos.X - CameraPost.X) +" < " + std::to_string(-640.f - 56.f + CameraPost.X)
				//+ " / " + std::to_string(ConvertPos.Y + CameraPost.Y) + " < " + std::to_string(-360.f - 56.f + CameraPost.Y));
			continue;
		}
		GetRenderUnit().SetTexture("TileMapTex", Sprite->GetTexture(Tile.SpriteIndex));
		Tile.SpriteData = Sprite->GetSpriteData(Tile.SpriteIndex);
		Tile.SpriteData.Pivot = { 0.0f, 0.0f };

		Pos.Position({ ConvertPos.X, ConvertPos.Y, 0.0f });

		Trans.WVP = Scale * Pos * RendererTrans.View * RendererTrans.Projection;

		GetRenderUnit().ConstantBufferLinkData("FTransform", Trans);
		GetRenderUnit().ConstantBufferLinkData("ResultColor", Tile.ColorData);
		GetRenderUnit().ConstantBufferLinkData("FSpriteData", Tile.SpriteData);

		Unit.Render(_Camera, _DeltaTime);
	}

}

void UTileMapRenderer::SetTile(FVector _Pos, int _Spriteindex)
{
	// 이공식이?????
	FTileIndex Index = WorldPosToTileIndex(_Pos);

	SetTile(Index.X, Index.Y, _Spriteindex);
}

void UTileMapRenderer::RemoveTile(FVector _Pos)
{
	FTileIndex Index = WorldPosToTileIndex(_Pos);

	RemoveTile(Index.X, Index.Y);
}

void UTileMapRenderer::SetTile(int _X, int _Y, int _Spriteindex)
{
	FTileIndex Index = { _X,  _Y };

	FTileData& NewTile = Tiles[Index.Key];

	NewTile.Index = Index;
	NewTile.SpriteIndex = _Spriteindex;
	NewTile.SpriteData.CuttingPos = {0.0f, 0.0f};
	NewTile.SpriteData.CuttingSize = { 1.0f, 1.0f };
	NewTile.SpriteData.Pivot = { 0.5f, 0.5f };
	NewTile.ColorData.PlusColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	NewTile.ColorData.MulColor = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void UTileMapRenderer::RemoveTile(int _X, int _Y)
{
	FTileIndex Index = { _X,  _Y };

	if (false == Tiles.contains(Index.Key))
	{
		return;
	}

	Tiles.erase(Index.Key);
}


void UTileMapRenderer::ComponentTick(float _DeltaTime)
{
	URenderer::ComponentTick(_DeltaTime);
}

void UTileMapRenderer::Serialize(UEngineSerializer& _Ser)
{
	_Ser << static_cast<int>(TileMapType);
	_Ser << TileSize;
	_Ser << ImageSize;
	_Ser << TilePivot;
	std::string Name = Sprite->GetName();
	_Ser << Name;

	_Ser << static_cast<int>(Tiles.size());
	for (std::pair<const __int64, FTileData>& Pair : Tiles)
	{
		_Ser.Write(&Pair.second, sizeof(FTileData));
	}
}
// 데이터를 복구(할때)
void UTileMapRenderer::DeSerialize(UEngineSerializer& _Ser)
{
	Tiles.clear();

	_Ser.Read(&TileMapType, sizeof(int));
	_Ser >> TileSize;
	_Ser >> ImageSize;
	_Ser >> TilePivot;
	std::string Name;
	_Ser >> Name;


	int Count = 0;
	_Ser >> Count;
	for (size_t i = 0; i < Count; i++)
	{
		FTileData TileData;
		_Ser.Read(&TileData, sizeof(TileData));
		Tiles.insert({ TileData.Index.Key, TileData });
	}
}