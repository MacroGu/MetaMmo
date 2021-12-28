#include "EntityCallOreBase.h"
#include "EntityDef.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_OreBase::EntityBaseEntityCall_OreBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_OreBase::~EntityBaseEntityCall_OreBase()
{
}



EntityCellEntityCall_OreBase::EntityCellEntityCall_OreBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_OreBase::~EntityCellEntityCall_OreBase()
{
}


}