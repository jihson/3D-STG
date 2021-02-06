#include "StandardEngineFramework.h"
#include "Object.h"

using namespace HyEngine;

Object::Object()
	: m_bWantsDestroy(false)
{	
	m_id = UIDGen::Get()->GetUID();

}


Object::~Object()
{
	m_id = UIDGen::Get()->GetUID();
}
