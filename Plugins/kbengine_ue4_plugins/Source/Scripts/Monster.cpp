#include "Monster.h"
#include "Engine/KBEngine.h"


KBEngine::Monster::Monster()
{
}

KBEngine::Monster::~Monster()
{
}

void KBEngine::Monster::__init__()
{

}

void KBEngine::Monster::onDestroy()
{
	// 注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void KBEngine::Monster::OnAnimUpdate(const ANIM_INFO& arg1)
{

}

void KBEngine::Monster::OnAttack(const SKILL_INFO& arg1)
{

}