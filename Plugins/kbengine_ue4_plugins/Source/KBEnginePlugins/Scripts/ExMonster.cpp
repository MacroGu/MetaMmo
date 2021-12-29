#include "ExMonster.h"
#include "Scripts/ExEventData.h"
#include "Engine/KBEngine.h"
#include "ExCommon.h"

KBEngine::ExMonster::ExMonster()
{

}

KBEngine::ExMonster::~ExMonster()
{

}

void KBEngine::ExMonster::__init__()
{

}

void KBEngine::ExMonster::onDestroy()
{
	// 注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void KBEngine::ExMonster::OnAnimUpdate(const ANIM_INFO& arg1)
{
	UKBEventData_OnAnimUpdate* EventData = NewObject<UKBEventData_OnAnimUpdate>();

	EventData->EntityId = id();
	EventData->Speed = arg1.Speed;
	EventData->Direction = arg1.Direction;

	KBENGINE_EVENT_FIRE("OnAnimUpdate", EventData);
}

void KBEngine::ExMonster::onBaseHPChanged(int32 oldValue)
{
	UKBEventData_SetBaseHP* EventData = NewObject<UKBEventData_SetBaseHP>();
	EventData->EntityId = id();
	EventData->IsPlayer = isPlayer();
	EventData->BaseHP = BaseHP;
	KBENGINE_EVENT_FIRE("SetBaseHP", EventData);
}

void KBEngine::ExMonster::onHPChanged(int32 oldValue)
{
	UKBEventData_SetHP* EventData = NewObject<UKBEventData_SetHP>();
	EventData->EntityId = id();
	EventData->IsPlayer = isPlayer();
	EventData->HP = HP;
	KBENGINE_EVENT_FIRE("SetHP", EventData);
}

void KBEngine::ExMonster::OnAttack()
{
	// 告诉MMOGameMode该实体对应的角色播放攻击动画
	UKBEventData_OnAttack* EventData = NewObject<UKBEventData_OnAttack>();
	EventData->EntityId = id();
	KBENGINE_EVENT_FIRE("OnAttack", EventData);

}

