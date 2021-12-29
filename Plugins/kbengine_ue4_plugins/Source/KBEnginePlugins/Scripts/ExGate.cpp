#include "ExGate.h"
#include "Scripts/ExEventData.h"
#include "Engine/KBEngine.h"
#include "ExCommon.h"

KBEngine::ExGate::ExGate()
{

}

KBEngine::ExGate::~ExGate()
{

}

void KBEngine::ExGate::__init__()
{

}

void KBEngine::ExGate::onDestroy()
{
	// 注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}
