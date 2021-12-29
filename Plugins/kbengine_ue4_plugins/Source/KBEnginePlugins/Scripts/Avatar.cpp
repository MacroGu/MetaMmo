#include "Avatar.h"
#include "Engine/KBEngine.h"


KBEngine::Avatar::Avatar()
{
}

KBEngine::Avatar::~Avatar()
{
}

void KBEngine::Avatar::__init__()
{

}

void KBEngine::Avatar::onDestroy()
{
	// 注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void KBEngine::Avatar::OnAnimUpdate(const ANIM_INFO& arg1)
{

}

void KBEngine::Avatar::OnAttack(const SKILL_INFO& arg1)
{

}

void KBEngine::Avatar::ntfError(uint32 arg1)
{

}

void KBEngine::Avatar::ntfItemsChange(const ITEM_LIST& arg1, const UINT16_LIST& arg2)
{

}

void KBEngine::Avatar::ntfReceiveChat(const CHAT_INFO& arg1)
{

}

void KBEngine::Avatar::rspChangeName(uint32 arg1)
{

}

void KBEngine::Avatar::rspDigOre()
{

}

void KBEngine::Avatar::rspStopDigOre()
{

}

void KBEngine::Avatar::rspSwitchAvatar(uint32 arg1)
{

}