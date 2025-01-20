#include "PreCompile.h"
#include "EngineResources.h"
#include "EngineTexture.h"
#include <mutex>


// EngineCoreDll의 영역입니다.

std::mutex ResCritical_Section;

std::shared_ptr<UEngineResources> UEngineResources::Find(std::string_view _ResName, std::string_view _Name)
{
	std::string UpperString = UEngineString::ToUpper(_Name);

	if (false == ResMap[_ResName.data()].contains(UpperString))
	{
		return nullptr;
	}

	return ResMap[_ResName.data()][UpperString];
}

void UEngineResources::PushRes(std::shared_ptr<UEngineResources> _Res, const std::string_view _Info, std::string_view _Name, std::string_view _Path)
{
	std::string UpperName = UEngineString::ToUpper(_Name);
	//       텍스처에                  Player.png가 들어있는지 확인.
	if (true == ResMap[_Info.data()].contains(UpperName))
	{
		MSGASSERT("이미 로드한 리소스를 또 로드 하려고 했습니다" + std::string(_Info.data()) + "  " + _Name.data());
		return;
	}

	// 이걸 호출한 쪽의 영역으로 잡히게 된다.

	_Res->SetName(UpperName);
	_Res->Path = _Path;

	// 여기에다가 그냥 동기화를 걸면 됩니다.
	ResMap[_Info.data()].insert({UpperName, _Res });

	return;
}

void UEngineResources::ThreadSafePushRes(std::shared_ptr<UEngineResources> _Res, const std::string_view _Info, std::string_view _Name, std::string_view _Path)
{
	std::string UpperName = UEngineString::ToUpper(_Name);
	_Res->SetName(UpperName);
	_Res->Path = _Path;


	{
		// 여러개의 쓰레드가 접근할때
		// 이거 3줄 달라진거로 사실 끝나는 일이다. 
		// 여길 통과할수 있는건 단 1개의 쓰레드 뿐이다.
		std::lock_guard<std::mutex> Lock(ResCritical_Section);

		// ResMap <= 임계영역이라고 생각하는 것이다.

		//       텍스처에                  Player.png가 들어있는지 확인.
		if (true == ResMap[_Info.data()].contains(UpperName))
		{
			MSGASSERT("이미 로드한 리소스를 또 로드 하려고 했습니다" + std::string(_Info.data()) + "  " + _Name.data());
			return;
		}

		// 이걸 호출한 쪽의 영역으로 잡히게 된다.
		// ResCritical_Section.lock();
		ResMap[_Info.data()].insert({ UpperName, _Res });
		// ResCritical_Section.unlock();
	}
	return;
}
