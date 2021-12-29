#include "EntityCallSkillBase.h"
#include "EntityDef.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_SkillBase::EntityBaseEntityCall_SkillBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_SkillBase::~EntityBaseEntityCall_SkillBase()
{
}



EntityCellEntityCall_SkillBase::EntityCellEntityCall_SkillBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_SkillBase::~EntityCellEntityCall_SkillBase()
{
}


}