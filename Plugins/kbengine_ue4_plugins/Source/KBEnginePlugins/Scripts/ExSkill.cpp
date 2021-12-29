#include "ExSkill.h"
#include "Scripts/ExEventData.h"
#include "Engine/KBEngine.h"
#include "ExCommon.h"

KBEngine::ExSkill::ExSkill()
{

}

KBEngine::ExSkill::~ExSkill()
{

}

void KBEngine::ExSkill::__init__()
{

}

void KBEngine::ExSkill::onDestroy()
{
	// 注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}
