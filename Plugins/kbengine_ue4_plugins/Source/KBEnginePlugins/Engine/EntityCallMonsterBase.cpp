#include "EntityCallMonsterBase.h"
#include "EntityDef.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_MonsterBase::EntityBaseEntityCall_MonsterBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_MonsterBase::~EntityBaseEntityCall_MonsterBase()
{
}



EntityCellEntityCall_MonsterBase::EntityCellEntityCall_MonsterBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_MonsterBase::~EntityCellEntityCall_MonsterBase()
{
}

void EntityCellEntityCall_MonsterBase::AnimUpdate(const ANIM_INFO& arg1)
{
	Bundle* pBundleRet = newCall("AnimUpdate", 0);
	if(!pBundleRet)
		return;

	((DATATYPE_ANIM_INFO*)EntityDef::id2datatypes[32])->addToStreamEx(*pBundleRet, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_MonsterBase::Attack(const SKILL_INFO& arg1)
{
	Bundle* pBundleRet = newCall("Attack", 0);
	if(!pBundleRet)
		return;

	((DATATYPE_SKILL_INFO*)EntityDef::id2datatypes[29])->addToStreamEx(*pBundleRet, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_MonsterBase::Relive()
{
	Bundle* pBundleRet = newCall("Relive", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}

void EntityCellEntityCall_MonsterBase::ReqChangeEnage(int32 arg1)
{
	Bundle* pBundleRet = newCall("ReqChangeEnage", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeInt32(arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_MonsterBase::ReqStartDamage(const SKILL_INFO& arg1, const ENTITY_LIST& arg2)
{
	Bundle* pBundleRet = newCall("ReqStartDamage", 0);
	if(!pBundleRet)
		return;

	((DATATYPE_SKILL_INFO*)EntityDef::id2datatypes[29])->addToStreamEx(*pBundleRet, arg1);
	((DATATYPE_ENTITY_LIST*)EntityDef::id2datatypes[25])->addToStreamEx(*pBundleRet, arg2);
	sendCall(NULL);
}


}