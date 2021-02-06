#pragma once



//enum class RenderType
//{
//	RenderOpaque = 0x0001,
//	RenderAlpha = 0x0002,
//	RenderUI = 0x0004,
//	RenderDebug = 0x0008,
//	None = 0x0010,
//};
struct RenderType
{
	static const DWORD RenderOpaque = 0x0001;
	static const DWORD RenderAlpha = 0x0002;
	static const DWORD RenderUI = 0x0004;
	static const DWORD RenderDebug = 0x0008;
	static const DWORD None = 0x0010;
};
//enum class LogicType
//{
//	Update = 0x0001,
//	LateUpdate = 0x0002,
//	None = 0x0004,
//};
struct ENGINE_DLL BehaviourType
{
	static const DWORD Update = 0x0001;
	static const DWORD LateUpdate = 0x0002;
	static const DWORD None = 0x0004;
};

namespace Tags
{
	static const std::wstring Default = L"Default";
	static const std::wstring Player = L"Player";
	static const std::wstring Obstacle = L"Obstacle";
	static const std::wstring Enemy = L"Enemy";
}

enum class Layers
{
	Defautl = 0x0001,
	UI = 0x0002,


};

enum class ERenderType
{
	RenderOpaque,
	RenderAlpha,
};

enum class EUpdateResult
{
	Continue,
	Stop,
};