#include "ExAccount.h"
#include "Scripts/ExEventData.h"
#include "Engine/KBEngine.h"
#include "ExCommon.h"



KBEngine::ExAccount::ExAccount()
{

}

KBEngine::ExAccount::~ExAccount()
{

}

void KBEngine::ExAccount::__init__()
{
	// 注册时间
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqCreateRole", "ReqCreateRole", [this](const UKBEventData* EventData) {
		const UKBEventData_ReqCreateRole* ServerData = Cast<UKBEventData_ReqCreateRole>(EventData);

		pBaseEntityCall->ReqCreateRole(ServerData->RoleType, ServerData->Name);
		});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqRemoveRole", "ReqRemoveRole", [this](const UKBEventData* EventData) {
		const UKBEventData_ReqRemoveRole* ServerData = Cast<UKBEventData_ReqRemoveRole>(EventData);

		pBaseEntityCall->ReqRemoveRole(ServerData->RoleInfo.Name);
		});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqSelectRoleGame", "ReqSelectRoleGame", [this](const UKBEventData* EventData) {
		const UKBEventData_ReqSelectRoleGame* ServerData = Cast<UKBEventData_ReqSelectRoleGame>(EventData);

		pBaseEntityCall->ReqSelectRoleGame(ServerData->RoleInfo.Dbid);
		});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqRoomList", "ReqRoomList", [this](const UKBEventData* EventData) 
		{
			pBaseEntityCall->ReqRoomList();
		});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqCreateRoom", "ReqCreateRoom", [this](const UKBEventData* EventData) 
		{
			const UKBEventData_ReqCreateRoom* ServerData = Cast<UKBEventData_ReqCreateRoom>(EventData);
			pBaseEntityCall->ReqCreateRoom(ServerData->RoomName);
		});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("SelectRoomGame", "SelectRoomGame", [this](const UKBEventData* EventData)
		{
			const UKBEventData_SelectRoomGame* ServerData = Cast<UKBEventData_SelectRoomGame>(EventData);
			pBaseEntityCall->SelectRoomGame(ServerData->RoomId);
		});

	// 触发登录成功事件
	UKBEventData_onLoginSuccessfully* EventData = NewObject<UKBEventData_onLoginSuccessfully>();
	EventData->entity_uuid = KBEngineApp::getSingleton().entity_uuid();
	EventData->entity_id = id();
	KBENGINE_EVENT_FIRE("onLoginSuccessfully", EventData);

	// 向服务端请求获取角色列表
	pBaseEntityCall->ReqRoleList();

}

void KBEngine::ExAccount::OnReqRoleList(const ROLE_LIST& arg1)
{
	UKBEventData_OnReqRoleList* EventData = NewObject<UKBEventData_OnReqRoleList>();

	for (int i = 0; i < arg1.Value.Num(); ++i)
	{
		// 保存角色列表到本地变量
		ROLE_INFO LocalInfo;
		LocalInfo.Dbid = arg1.Value[i].Dbid;
		LocalInfo.Name = arg1.Value[i].Name;
		LocalInfo.RoleType = arg1.Value[i].RoleType;
		LocalInfo.Data.DataType = arg1.Value[i].Data.DataType;
		LocalInfo.Data.DataValue = arg1.Value[i].Data.DataValue;

		RoleList.Value.Add(LocalInfo);

		// 保存角色列到回调方法参数类
		FROLE_INFO RoleInfo;
		RoleInfo.InitData(LocalInfo.Dbid, LocalInfo.Name, LocalInfo.RoleType, (LastSelRole == LocalInfo.Dbid));
		EventData->RoleList.Add(RoleInfo);
	}

	KBENGINE_EVENT_FIRE("OnReqRoleList", EventData);
}


void KBEngine::ExAccount::OnReqRoomList(const ROOM_LIST& arg1)
{
	UKBEventData_OnReqRoomList* EventData = NewObject<UKBEventData_OnReqRoomList>();

	for (int i = 0; i < arg1.Value.Num(); ++i)
	{
		FROOM_INFO RoomInfo;
		RoomInfo.InitData(arg1.Value[i].RoomId, arg1.Value[i].Name);
		EventData->RoomList.Add(RoomInfo);
	}

	// 告诉UE4获取房间列表
	KBENGINE_EVENT_FIRE("OnReqRoomList", EventData);

}

void KBEngine::ExAccount::OnCreateRole(uint8 arg1, const ROLE_INFO& arg2)
{
	UKBEventData_OnCreateRole* EventData = NewObject<UKBEventData_OnCreateRole>();

	ROLE_INFO LocalInfo;
	LocalInfo.Dbid = arg2.Dbid;
	LocalInfo.Name = arg2.Name;
	LocalInfo.RoleType = arg2.RoleType;
	LocalInfo.Data.DataType = arg2.Data.DataType;
	LocalInfo.Data.DataValue = arg2.Data.DataValue;

	EventData->RoleInfo.InitData(arg2.Dbid, arg2.Name, arg2.RoleType, (LastSelRole == arg2.Dbid));

	EventData->ErrorCode = arg1;

	// 判断创建结果
	if (arg1 == 0)
	{
		// 将数据保存到本地
		RoleList.Value.Add(LocalInfo);
	}
	else if(arg1 == 1)
	{
		// 角色名字重复
		DDH::Debug() << "ExAccount::OnCreateRole : Repetition Name --> " << arg2.Name << DDH::Endl();
	}
	else if (arg1 == 2)
	{
		// 角色类型重复
		DDH::Debug() << "ExAccount::OnCreateRole : Repetition RoleType --> " << arg2.RoleType << DDH::Endl();
	}

	// 通知UE4 创建结果
	KBENGINE_EVENT_FIRE("OnCreateRole", EventData);
}

void KBEngine::ExAccount::OnCreateRoom(uint8 arg1, const ROOM_INFO& arg2)
{
	if (arg1 == 1)
	{
		DDH::Debug() << "ExAccount::OnCreateRoom Failed By Name --> " << arg2.Name << DDH::Endl();
		return;
	}

	UKBEventData_OnCreateRoom* EventData = NewObject<UKBEventData_OnCreateRoom>();

	EventData->RoomInfo.InitData(arg2.RoomId, arg2.Name);

	// 告诉UE4 创建房间成功
	KBENGINE_EVENT_FIRE("OnCreateRoom", EventData)
}

void KBEngine::ExAccount::OnRemoveRole(uint64 arg1)
{
	int InfoIndex = -1;
	for (int i = 0; i < RoleList.Value.Num(); ++i)
	{
		if (RoleList.Value[i].Dbid == arg1)
		{
			InfoIndex = i;
			break;
		}
	}

	// 判断有没有找到对应角色
	if (InfoIndex < 0)
	{
		DDH::Debug() << "ExAccount::OnRemoveRole : Did not found the role by Dbid --> " << arg1 << DDH::Endl();
		return;
	}

	UKBEventData_OnRemoveRole* EventData = NewObject<UKBEventData_OnRemoveRole>();
	EventData->RoleInfo.InitData(RoleList.Value[InfoIndex].Dbid, RoleList.Value[InfoIndex].Name, RoleList.Value[InfoIndex].RoleType, (LastSelRole == RoleList.Value[InfoIndex].Dbid));

	// 通知UE4 移除角色结果
	KBENGINE_EVENT_FIRE("OnRemoveRole", EventData);

}

void KBEngine::ExAccount::OnSelectRoleGame(uint8 arg1, uint64 arg2)
{
	// 判断结果
	if (arg1 == 1)
	{
		DDH::Debug() << "ExAccount::OnSelectRoleGame NoRole By Dbid --> " << arg2 << DDH::Endl();
		return;
	}

	UKBEventData_OnSelectRoleGame* EventData = NewObject<UKBEventData_OnSelectRoleGame>();
	EventData->Dbid = arg2;

	// 通知UE4 选择角色成功
	KBENGINE_EVENT_FIRE("OnSelectRoleGame", EventData);

}

void KBEngine::ExAccount::onDestroy()
{
	// 注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();

}