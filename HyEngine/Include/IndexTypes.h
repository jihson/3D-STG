#pragma once

namespace HyEngine
{
	struct Index16
	{
		WORD _1, _2, _3;
		static const D3DFORMAT FMT;
	};
	struct Index32
	{
		DWORD _1, _2, _3;
		static const D3DFORMAT FMT;
	};

}