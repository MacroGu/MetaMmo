#include "EntityCallWorldBase.h"
#include "EntityDef.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_WorldBase::EntityBaseEntityCall_WorldBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_WorldBase::~EntityBaseEntityCall_WorldBase()
{
}



EntityCellEntityCall_WorldBase::EntityCellEntityCall_WorldBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_WorldBase::~EntityCellEntityCall_WorldBase()
{
}


}