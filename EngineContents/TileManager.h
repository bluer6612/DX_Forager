#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/TileMapRenderer.h>

enum class UICollisionGroup
{
	Cursor,
	Ground,
	Building,
	Croppatch,
	Panel,
};

static int Money = 400;
static int Bio = 8;
static int BioExchange = 1;

// Ό³Έν :
class ATileManager : public AActor
{
public:
	ATileManager();
	~ATileManager();

	ATileManager(const ATileManager& _Other) = delete;
	ATileManager(ATileManager&& _Other) noexcept = delete;
	ATileManager& operator=(const ATileManager& _Other) = delete;
	ATileManager& operator=(ATileManager&& _Other) noexcept = delete;

	void BeginPlay();

	void Tick(float _DeltaTime);

	std::shared_ptr<class USpriteRenderer> PivotSpriteRenderer;
	std::shared_ptr<class UTileMapRenderer> GroundTileMap;
	std::shared_ptr<class UTileMapRenderer> CroppatchTile;

	//USpriteRenderer* GetCursorImage()
	//{
	//	return CursorImage;
	//}

	//void SetMenuPanelUI(AMenuPanelUI* const _MenuPanelUI)
	//{
	//	MenuPanelUI = _MenuPanelUI;
	//}

	//void TapButtonIn();
	//void TapButtonOut();
	//void TapButtonStay(AActor* _Actor, FTransform _Index);

	//void PanelButtonTileEnter(AActor* _Actor, FTransform _Index);
	//void PanelButtonTileStay(AActor* _Actor, FTransform _Index);
	//void PanelButtonTileEnd(AActor* _Actor, FTransform _Index);

	//void CreateText(AScore* _AScore, FVector2D _Location, int _Value, int _Order = false, bool _Active = true, ERenderOrder _ERenderOrder = ERenderOrder::UIUP)
	//{
	//	if (_AScore != ResourcesText[4])
	//	{
	//		_AScore->SetTextSpriteName("Text.png");
	//	}
	//	else
	//	{
	//		_AScore->SetTextSpriteName("TextGreen.png");
	//	}
	//	_AScore->SetOrder(_ERenderOrder);
	//	_AScore->SetTextScale({ 7.5f, 15.f });
	//	_AScore->SetActorLocation(_Location);
	//	_AScore->SetValue(_Value, _Order, _Active);
	//}


	//std::vector<class Tile*> CropsAllVector;
	//USpriteRenderer* CroppatchTileImage[1000] = {};

	//std::vector<class Tile*> StorageTilesVector;
	//std::vector<class Tile*> WellTilesVector;
	//std::vector<FIntPoint> FarmingStats;

	//AScore* ResourcesText[10] = {};
	//AScore* CropsCountText[CropsCount] = {};
	//AScore* CropsPriceText[CropsCount] = {};

	//AMenuPanelUI* MenuPanelUI = nullptr;

	int CropsLock = 2;
protected:

private:
	class U2DCollision* CursorCollision = nullptr;
	class USpriteRenderer* CursorImage = nullptr;

	class USpriteRenderer* SRFarmInfo = nullptr;
	class USpriteRenderer* SRButtonBlack = nullptr;
	class USpriteRenderer* SRTapWhite = nullptr;

	bool CursorOnTap = false;
	int NowSelectCrops = -1;
	int NowSelectTap = 0;
	int TapTimer = 0;

	std::vector<class U2DCollision*> PanelAllVector;
};