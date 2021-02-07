#pragma once
#include "LinearMath.h"

namespace HyEngine
{
	namespace Math
	{
		static D3DXVECTOR3 WorldMat2PosVec(const D3DXMATRIX& worldMat)
		{
			Vector3 posVec;
			posVec.x() = worldMat.m[3][0];
			posVec.y() = worldMat.m[3][1];
			posVec.z() = worldMat.m[3][2];
			return posVec;
		}
		static D3DXVECTOR3 WorldMat2ScaleVec(const D3DXMATRIX& worldMat)
		{
			Vector3 scaleVec;
			scaleVec.x() = worldMat.m[0][0];
			scaleVec.y() = worldMat.m[1][1];
			scaleVec.z() = worldMat.m[2][2];
			return scaleVec;
		}


	}
}

