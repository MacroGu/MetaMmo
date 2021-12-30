#include "Account.h"
#include "Scripts/ExEventData.h"
#include "Engine/KBEngine.h"


KBEngine::Account::Account()
{

}

KBEngine::Account::~Account()
{

}

void KBEngine::Account::__init__()
{

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("reqAvatarList", "reqAvatarList", [this](const UKBEventData* EventData) 
	{
		pBaseEntityCall->reqAvatarList();
	});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("reqCreateAvatar", "reqCreateAvatar", [this](const UKBEventData* EventData) 
	{
		const UKBEventData_reqCreateAvatar* ServerData = Cast<UKBEventData_reqCreateAvatar>(EventData);

		pBaseEntityCall->reqCreateAvatar(ServerData->RoleType, ServerData->Name, ServerData->Facade);

	});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("reqEnterGame", "reqEnterGame", [this](const UKBEventData* EventData) 
	{
		const UKBEventData_reqEnterGame* ServerData = Cast<UKBEventData_reqEnterGame>(EventData);

		pBaseEntityCall->reqEnterGame(ServerData->DatabaseID);
	});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("reqRemoveAvatar", "reqRemoveAvatar", [this](const UKBEventData* EventData)
	{
		const UKBEventData_reqRemoveAvatar* ServerData = Cast<UKBEventData_reqRemoveAvatar>(EventData);

		pBaseEntityCall->reqEnterGame(ServerData->dbid);
	});


	// 触发登录成功事件
	UKBEventData_onLoginSuccessfully* EventData = NewObject<UKBEventData_onLoginSuccessfully>();
	EventData->entity_uuid = KBEngineApp::getSingleton().entity_uuid();
	EventData->entity_id = id();
	KBENGINE_EVENT_FIRE("onLoginSuccessfully", EventData);

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
