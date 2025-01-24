#include "PreCompile.h"
#include "ContentsCore.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/EngineShader.h>
#include <EngineCore/EngineMaterial.h>
#include "PlayGameMode.h"
#include "LightGameMode.h"
#include "TileMapGameMode.h"
#include <EngineCore/HUD.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/EngineGUIWindow.h>
#include "TitleHUD.h"
#include "ContentsEditorGUI.h"
#include "LoadGameMode.h"
#include "MyGameInstance.h"

// #define은 그냥 무조건 복붙
CreateContentsCoreDefine(UContentsCore);

UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}


void UContentsCore::EngineStart(UEngineInitData& _Data)
{
	// mainwindow는 아무나 건들면 안된다.
	// 넌 컨텐츠잖아 엔진이 관리하는 윈도우라는게 존재하는지도 몰라야한다.

	GEngine->CreateGameInstance<MyGameInstance>();

	_Data.WindowPos = { 100, 100 };
	_Data.WindowSize = { 1280, 720 };

	ResourcesSetting();

	UEngineGUI::AllWindowOff();

	UEngineCore::CreateLevel<ALightGameMode, APawn, AHUD>("LightLevel");
	UEngineCore::CreateLevel<ALoadGameMode, APawn, AHUD>("LoadLevel");

	UEngineCore::OpenLevel("LoadLevel");

	/*UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
	std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
	Window->SetActive(true);*/
}

void UContentsCore::EngineTick(float _DeltaTime)
{

}

void UContentsCore::EngineEnd()
{

}