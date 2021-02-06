#include "StandardEngineFramework.h"
#include "TestComponent2.h"
#include "Camera.h"
#include "GameObject.h"



void TestComponent2::Update()
{
	static float angle = (3.0f * D3DX_PI) / 2.0f;
	static float cameraHeight = 0.0f;
	static float cameraHeightDirection = 5.0f;


	ENGINE->GetCamera()->SetPosition(cosf(angle) * 10.0f, cameraHeight, sinf(angle) * 10.0f);


	angle += 0.001f;
	if (angle >= 6.28f)
		angle = 0.0f;

	// compute the height of the camera for the next frame
	cameraHeight += cameraHeightDirection * 0.001f;
	if (cameraHeight >= 10.0f)
		cameraHeightDirection = -5.0f;

	if (cameraHeight <= -10.0f)
		cameraHeightDirection = 5.0f;


	// player contorl
	if (KEYBOARD->Press('W'))
	{
		GetTransform()->Translate(GetTransform()->Forward() * moveSpeed * TIMER->getDeltaTime());
	}
	if (KEYBOARD->Press('S'))
	{
		GetTransform()->Translate((GetTransform()->Forward() * -1) * moveSpeed * TIMER->getDeltaTime());
	}
	if (KEYBOARD->Press('A'))
	{
		GetTransform()->Translate((GetTransform()->Right() * -1) * moveSpeed * TIMER->getDeltaTime());
	}
	if (KEYBOARD->Press('D'))
	{
		GetTransform()->Translate((GetTransform()->Right()) * moveSpeed * TIMER->getDeltaTime());
	}


}

void TestComponent2::LateUpdate()
{
	int b = 0;
}

void TestComponent2::OnEnable()
{
}

void TestComponent2::OnDisable()
{
}

void TestComponent2::Initialize()
{
}
