#pragma once
#include <EngineCore/GameMode.h>

// ���� :
class APlayGameMode : public AGameMode
{
public:
	// constrcuter destructer
	APlayGameMode();
	~APlayGameMode();

	// delete Function
	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);


protected:
	void LevelChangeStart() override;

private:
	// �̷��� ��� ������ ���� �׿��ٰ� �����ϴµ�. ��������� �ִ�.
	// ATitleLogo* Logo; => ���۸� ������ ��Ȱ.
	std::shared_ptr<class ATitleLogo> Logo;
};

//
//// �ﰢ�� �ϳ�
//struct FNaviData
//{
//	int Index;
//
//	FVector Arr[3];
//
//	int ArrIndex[3];
//
//	// std::vector<FNaviData*> LinkArr;
//	// std::vector<int> Arr;
//
//	void Intersect(AActor* Player, float& Dis)
//	{
//		// DirectX::TriangleTests::Intersects()
//	}
//};
//
//class ANaviMeshManager : AActor
//{
//	std::vector<FNaviData> Data;
//
//	void LoadModel(std::string_view _Path)
//	{
//		std::vector<FVector> AllVector;
//	}
//
//	// ������ ������ָ� �˴ϴ�.
//	void LinkProgress();
//};
//
//class Player
//{
//	FNaviData* CurNaviMesh;
//};