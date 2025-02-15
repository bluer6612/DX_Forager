#pragma once

typedef __int8 int8;


enum class EProjectionType : int8
{
	Perspective,
	Orthographic,
};

enum class EEngineCameraType : int8
{
	MainCamera,
	UICamera = 127,
};

// 1바이트 정수 로 쉐이더를 만들고 싶으면 아래와 같이 하면 됩니다.
enum class EShaderType : int8
{
	VS, // 버텍스
	HS, // 
	DS,
	GS,
	PS,
	CS,
	MAX
};

static const int TilemapCount = 500;
static const float MoveSpeed = 400.0f;