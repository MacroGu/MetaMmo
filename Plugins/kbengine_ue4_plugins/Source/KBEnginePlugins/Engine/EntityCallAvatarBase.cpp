#include "EntityCallAvatarBase.h"
#include "EntityDef.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_AvatarBase::EntityBaseEntityCall_AvatarBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_AvatarBase::~EntityBaseEntityCall_AvatarBase()
{
}

void EntityBaseEntityCall_AvatarBase::reqSwitchAvatar()
{
	Bundle* pBundleRet = newCall("reqSwitchAvatar", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}



EntityCellEntityCall_AvatarBase::EntityCellEntityCall_AvatarBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_AvatarBase::~EntityCellEntityCall_AvatarBase()
{
}

void EntityCellEntityCall_AvatarBase::AnimUpdate(const ANIM_INFO& arg1)
{
	Bundle* pBundleRet = newCall("AnimUpdate", 0);
	if(!pBundleRet)
		return;

	((DATATYPE_ANIM_INFO*)EntityDef::id2datatypes[32])->addToStreamEx(*pBundleRet, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::Attack(const SKILL_INFO& arg1)
{
	Bundle* pBundleRet = newCall("Attack", 0);
	if(!pBundleRet)
		return;

	((DATATYPE_SKILL_INFO*)EntityDef::id2datatypes[29])->addToStreamEx(*pBundleRet, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::Relive()
{
	Bundle* pBundleRet = newCall("Relive", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::ReqChangeEnage(int32 arg1)
{
	Bundle* pBundleRet = newCall("ReqChangeEnage", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeInt32(arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::ReqStartDamage(const SKILL_INFO& arg1, const ENTITY_LIST& arg2)
{
	Bundle* pBundleRet = newCall("ReqStartDamage", 0);
	if(!pBundleRet)
		return;

	((DATATYPE_SKILL_INFO*)EntityDef::id2datatypes[29])->addToStreamEx(*pBundleRet, arg1);
	((DATATYPE_ENTITY_LIST*)EntityDef::id2datatypes[25])->addToStreamEx(*pBundleRet, arg2);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::reqChangeJump(int8 arg1)
{
	Bundle* pBundleRet = newCall("reqChangeJump", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeInt8(arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::reqChangeMoveH(int8 arg1)
{
	Bundle* pBundleRet = newCall("reqChangeMoveH", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeInt8(arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::reqChangeMoveLevel(int8 arg1)
{
	Bundle* pBundleRet = newCall("reqChangeMoveLevel", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeInt8(arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::reqChangeMoveV(int8 arg1)
{
	Bundle* pBundleRet = newCall("reqChangeMoveV", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeInt8(arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::reqChangeName(const FString& arg1)
{
	Bundle* pBundleRet = newCall("reqChangeName", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUnicode(arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::reqDigOre(int32 arg1)
{
	Bundle* pBundleRet = newCall("reqDigOre", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeInt32(arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::reqExecInnerFunc(const FString& arg1, const FString& arg2)
{
	Bundle* pBundleRet = newCall("reqExecInnerFunc", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeString(arg1);
	pBundleRet->writeString(arg2);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::reqMoveItem(uint16 arg1, uint16 arg2)
{
	Bundle* pBundleRet = newCall("reqMoveItem", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint16(arg1);
	pBundleRet->writeUint16(arg2);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::reqPickupItem(int32 arg1, const UINT64_LIST& arg2)
{
	Bundle* pBundleRet = newCall("reqPickupItem", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeInt32(arg1);
	((DATATYPE_UINT64_LIST*)EntityDef::id2datatypes[24])->addToStreamEx(*pBundleRet, arg2);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::reqSendChatMessage(uint64 arg1, uint8 arg2, const FString& arg3)
{
	Bundle* pBundleRet = newCall("reqSendChatMessage", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint64(arg1);
	pBundleRet->writeUint8(arg2);
	pBundleRet->writeUnicode(arg3);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::reqSetupInnerProp(const FString& arg1, const FString& arg2)
{
	Bundle* pBundleRet = newCall("reqSetupInnerProp", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeString(arg1);
	pBundleRet->writeString(arg2);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::reqSplitItemNum(uint16 arg1, uint32 arg2, uint16 arg3)
{
	Bundle* pBundleRet = newCall("reqSplitItemNum", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint16(arg1);
	pBundleRet->writeUint32(arg2);
	pBundleRet->writeUint16(arg3);
	sendCall(NULL);
}

void EntityCellEntityCall_AvatarBase::reqStopDigOre()
{
	Bundle* pBundleRet = newCall("reqStopDigOre", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}


}