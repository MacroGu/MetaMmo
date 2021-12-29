#include "ExFlob.h"
#include "Scripts/ExEventData.h"
#include "Engine/KBEngine.h"
#include "ExCommon.h"

KBEngine::ExFlob::ExFlob()
{

}

KBEngine::ExFlob::~ExFlob()
{

}

void KBEngine::ExFlob::__init__()
{

}

void KBEngine::ExFlob::onDestroy()
{
	// 注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}
