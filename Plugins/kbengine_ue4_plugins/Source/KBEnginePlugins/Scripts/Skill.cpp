#include "Skill.h"
#include "Engine/KBEngine.h"


KBEngine::Skill::Skill()
{
}

KBEngine::Skill::~Skill()
{
}

void KBEngine::Skill::__init__()
{

}

void KBEngine::Skill::onDestroy()
{
	// 注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}
