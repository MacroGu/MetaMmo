#include "ItemDropPackage.h"
#include "Engine/KBEngine.h"


KBEngine::ItemDropPackage::ItemDropPackage()
{
}

KBEngine::ItemDropPackage::~ItemDropPackage()
{
}

void KBEngine::ItemDropPackage::__init__()
{

}

void KBEngine::ItemDropPackage::onDestroy()
{
	// 注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}
