#pragma once

namespace HyEngine
{
	__interface ILight
	{
		virtual void Update() = 0;
		virtual void Render() = 0;
	};

}
