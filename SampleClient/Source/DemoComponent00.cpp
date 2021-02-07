#include "StandardEngineFramework.h"
#include "DemoComponent00.h"
#include "Camera.h"
#include "GameObject.h"



void DemoComponent00::Update()
{


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

void DemoComponent00::LateUpdate()
{
	int b = 0;
}

void DemoComponent00::OnEnable()
{
}

void DemoComponent00::OnDisable()
{
}

void DemoComponent00::Initialize()
{

}
