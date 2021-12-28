#include "EntityCallSceneMgrBase.h"
#include "EntityDef.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_SceneMgrBase::EntityBaseEntityCall_SceneMgrBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_SceneMgrBase::~EntityBaseEntityCall_SceneMgrBase()
{
}



EntityCellEntityCall_SceneMgrBase::EntityCellEntityCall_SceneMgrBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_SceneMgrBase::~EntityCellEntityCall_SceneMgrBase()
{
}


}