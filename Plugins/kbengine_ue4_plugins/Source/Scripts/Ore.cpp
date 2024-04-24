#include "Ore.h"
#include "Engine/KBEngine.h"


KBEngine::Ore::Ore()
{
}

KBEngine::Ore::~Ore()
{
}

void KBEngine::Ore::__init__()
{

}

void KBEngine::Ore::onDestroy()
{
	// 注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}
