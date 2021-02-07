

#include "stdafx.h"

#include <Windows.h>
#include <time.h>
//#include "TestScene.h"
#include "DemoScene00.h"
#include "DemoCamera00.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, PSTR pScmdl, int iCmdShow)
{
	srand(static_cast<unsigned>(time(NULL)));

	Application STG_Demo(L"STG Demo");

	EngineConfig engineConfig;

	engineConfig.scenes.push_back(new DemoScene00());
	engineConfig.defaultSceneIndex = 0;
	engineConfig.camera = new DemoCamera00();

	if (STG_Demo.Init(hInst, iCmdShow, engineConfig))
	{
		STG_Demo.Run();
	}
	STG_Demo.Exit();

	return 0;
}