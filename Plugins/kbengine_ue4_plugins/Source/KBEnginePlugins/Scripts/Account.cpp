#include "Account.h"
#include "Engine/KBEngine.h"


KBEngine::Account::Account()
{

}

KBEngine::Account::~Account()
{

}

void KBEngine::Account::__init__()
{


}

void KBEngine::Account::onDestroy()
{
	// 注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();

}

void KBEngine::Account::rspAvatarList(const AVATAR_BRIEF_INFO_LIST& arg1, uint64 arg2)
{

}

void KBEngine::Account::rspCreateAvatar(uint32 arg1)
{

}

void KBEngine::Account::rspEnterGame(uint32 arg1)
{

}

void KBEngine::Account::rspRemoveAvatar(uint32 arg1)
{

}

void KBEngine::Account::rspSwitchAvatar(uint32 arg1)
{

}
