#include "StandardEngineFramework.h"
#include "Layer.h"

using namespace HyEngine;


const std::unordered_map<std::wstring, UINT> Layer::layersMap =
{
	{ L"Default", Default },
	{ L"UI", UI },
	{ L"Player", Player }
};