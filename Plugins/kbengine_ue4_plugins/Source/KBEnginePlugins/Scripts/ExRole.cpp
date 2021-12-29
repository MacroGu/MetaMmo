#include "ExRole.h"
#include "Scripts/ExEventData.h"
#include "Engine/KBEngine.h"
#include "ExCommon.h"


KBEngine::ExRole::ExRole()
{
}

KBEngine::ExRole::~ExRole()
{
}

void KBEngine::ExRole::__init__()
{
	// 如果是本地玩家
	if (isPlayer())
	{
		// 注册动作同步事件
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("AnimUpdate", "AnimUpdate", [this](const UKBEventData* EventData) {
				const UKBEventData_AnimUpdate* ServerData = Cast<UKBEventData_AnimUpdate>(EventData);
				ANIM_INFO AnimInfo;
				AnimInfo.Speed = ServerData->Speed;
				AnimInfo.Direction = ServerData->Direction;
				pCellEntityCall->AnimUpdate(AnimInfo);
			});	

		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("Relive", "Relive", [this](const UKBEventData* EventData) 
			{
				pCellEntityCall->Relive();
			});

		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqBagList", "ReqBagList", [this](const UKBEventData* EventData)
			{
				pBaseEntityCall->ReqBagList();
			});

		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("PassGood", "PassGood", [this](const UKBEventData* EventData)
			{
				const UKBEventData_PassGood* ServerData = Cast<UKBEventData_PassGood>(EventData);
				
				pBaseEntityCall->PassGood(ServerData->ArcBagType, ServerData->ArcBlockId, ServerData->DesBagType, ServerData->DesBlockId);
			});

		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReduceGood", "ReduceGood", [this](const UKBEventData* EventData)
			{
				const UKBEventData_ReduceGood* ServerData = Cast<UKBEventData_ReduceGood>(EventData);

				pBaseEntityCall->ReduceGood(ServerData->BagType, ServerData->BlockId);
			});
		//注册攻击事件
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("Attack", "Attack", [this](const UKBEventData* EventData)
			{
				const UKBEventData_Attack* ServerData = Cast<UKBEventData_Attack>(EventData);
				SKILL_INFO SkillInfo;
				SkillInfo.SkillId = ServerData->SkillId;
				SkillInfo.SpawnPos = ServerData->SpawnPos;
				SkillInfo.TargetPos = ServerData->TargetPos;
				pCellEntityCall->Attack(SkillInfo);
			});
		//注册发送聊天消息事件
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("SendChatInfo", "SendChatInfo", [this](const UKBEventData* EventData)
			{
				const UKBEventData_SendChatInfo* ServerData = Cast<UKBEventData_SendChatInfo>(EventData);

				pBaseEntityCall->SendChatInfo(ServerData->Message);
			});
		// 注册离开房间事件
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("LeaveRoom", "LeaveRoom", [this](const UKBEventData* EventData)
			{
				pBaseEntityCall->LeaveRoom();
			});
		// 注册跳转场景事件
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqTeleportRoom", "ReqTeleportRoom", [this](const UKBEventData* EventData)
			{
				const UKBEventData_ReqTeleportRoom* ServerData = Cast<UKBEventData_ReqTeleportRoom>(EventData);
				pBaseEntityCall->ReqTeleportRoom(ServerData->DesRoomId);
			});
	}

}

void KBEngine::ExRole::onDestroy()
{
	// 注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void KBEngine::ExRole::OnAnimUpdate(const ANIM_INFO& arg1)
{
	UKBEventData_OnAnimUpdate* EventData = NewObject<UKBEventData_OnAnimUpdate>();

	EventData->EntityId = id();
	EventData->Speed = arg1.Speed;
	EventData->Direction = arg1.Direction;

	KBENGINE_EVENT_FIRE("OnAnimUpdate", EventData);

}

void KBEngine::ExRole::onBaseHPChanged(int32 oldValue)
{
	UKBEventData_SetBaseHP* EventData = NewObject<UKBEventData_SetBaseHP>();
	EventData->EntityId = id();
	EventData->IsPlayer = isPlayer();
	EventData->BaseHP = BaseHP;
	KBENGINE_EVENT_FIRE("SetBaseHP", EventData);
}

void KBEngine::ExRole::onHPChanged(int32 oldValue)
{
	UKBEventData_SetHP* EventData = NewObject<UKBEventData_SetHP>();
	EventData->EntityId = id();
	EventData->IsPlayer = isPlayer();
	EventData->HP = HP;
	KBENGINE_EVENT_FIRE("SetHP", EventData);
}

void KBEngine::ExRole::onDefenseChanged(int32 oldValue)
{
	UKBEventData_SetDefense* EventData = NewObject<UKBEventData_SetDefense>();
	EventData->EntityId = id();
	EventData->Defense = Defense;
	KBENGINE_EVENT_FIRE("SetDefense", EventData);
}

void KBEngine::ExRole::onPowerRatioChanged(float oldValue)
{
	UKBEventData_SetPowerRatio* EventData = NewObject<UKBEventData_SetPowerRatio>();
	EventData->EntityId = id();
	EventData->PowerRatio = PowerRatio;
	KBENGINE_EVENT_FIRE("SetPowerRatio", EventData);
}

void KBEngine::ExRole::onSpeedRatioChanged(float oldValue)
{
	UKBEventData_SetSpeedRatio* EventData = NewObject<UKBEventData_SetSpeedRatio>();
	EventData->EntityId = id();
	EventData->SpeedRatio = SpeedRatio;
	KBENGINE_EVENT_FIRE("SetSpeedRatio", EventData);
}

void KBEngine::ExRole::OnAttack()
{
	// 告诉MMOGameMode该实体对应的角色播放攻击动画
	UKBEventData_OnAttack* EventData = NewObject<UKBEventData_OnAttack>();
	EventData->EntityId = id();
	KBENGINE_EVENT_FIRE("OnAttack", EventData);
}

void KBEngine::ExRole::OnIncreaseGood(uint8 arg1, const GOOD_INFO& arg2)
{
	UKBEventData_OnIncreaseGood* EventData = NewObject<UKBEventData_OnIncreaseGood>();
	EventData->BagType = arg1;
	EventData->GoodInfo.InitInfo(arg2.BlockId, arg2.GoodId, arg2.Number);
	KBENGINE_EVENT_FIRE("OnIncreaseGood", EventData);
}

void KBEngine::ExRole::OnPassGood(uint8 arg1, const GOOD_INFO& arg2, uint8 arg3, const GOOD_INFO& arg4)
{
	UKBEventData_OnPassGood* EventData = NewObject<UKBEventData_OnPassGood>();
	EventData->ArcBagType = arg1;
	EventData->ArcGoodInfo.InitInfo(arg2.BlockId, arg2.GoodId, arg2.Number);
	EventData->DesBagType = arg3;
	EventData->DesGoodInfo.InitInfo(arg4.BlockId, arg4.GoodId, arg4.Number);
	KBENGINE_EVENT_FIRE("OnPassGood", EventData);
}

void KBEngine::ExRole::OnReduceGood(uint8 arg1, uint8 arg2, const GOOD_INFO& arg3)
{
	UKBEventData_OnReduceGood* EventData = NewObject<UKBEventData_OnReduceGood>();
	EventData->ReduceRes = arg1;
	EventData->BagType = arg2;
	EventData->GoodInfo.InitInfo(arg3.BlockId, arg3.GoodId, arg3.Number);
	KBENGINE_EVENT_FIRE("OnReduceGood", EventData);
}

void KBEngine::ExRole::OnReqBagList(const BAG_INFO& arg1, const BAG_INFO& arg2, const BAG_INFO& arg3, const BAG_INFO& arg4)
{
	UKBEventData_OnReqBagList* EventData = NewObject<UKBEventData_OnReqBagList>();

	for (auto Info : arg1.Value)
	{
		FGOOD_INFO GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		EventData->MainBag.Add(GoodInfo);
	}

	for (auto Info : arg2.Value)
	{
		FGOOD_INFO GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		EventData->SkillBag.Add(GoodInfo);
	}

	for (auto Info : arg3.Value)
	{
		FGOOD_INFO GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		EventData->BuffBag.Add(GoodInfo);
	}

	for (auto Info : arg4.Value)
	{
		FGOOD_INFO GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		EventData->EquipBag.Add(GoodInfo);
	}

	KBENGINE_EVENT_FIRE("OnReqBagList", EventData);
}

void KBEngine::ExRole::AcceptChatList(const CHAT_LIST& arg1)
{
	UKBEventData_AcceptChatList* EventData = NewObject<UKBEventData_AcceptChatList>();
	
	for (auto Info : arg1.Value)
	{
		FCHAT_INFO ChatInfo;
		ChatInfo.InitInfo(Info.Name, Info.Date, Info.Message);
		EventData->ChatList.Add(ChatInfo);
	}

	KBENGINE_EVENT_FIRE("AcceptChatList", EventData);
}

void KBEngine::ExRole::UpdateCountDown(uint32 arg1)
{
	UKBEventData_UpdateCountDown* EventData = NewObject<UKBEventData_UpdateCountDown>();
	EventData->CountDown = arg1;
	KBENGINE_EVENT_FIRE("UpdateCountDown", EventData);
}

void KBEngine::ExRole::ShowResultList(const FString& arg1, uint32 arg2, const FString& arg3, uint32 arg4, const FString& arg5, uint32 arg6)
{
	UKBEventData_ShowResultList* EventData = NewObject<UKBEventData_ShowResultList>();
	EventData->NameOne = arg1;
	EventData->CountOne = arg2;
	EventData->NameTwo = arg3;
	EventData->CountTwo = arg4;
	EventData->NameThree = arg5;
	EventData->CountThree = arg6;

	KBENGINE_EVENT_FIRE("ShowResultList", EventData);

}
