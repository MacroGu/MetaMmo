#include "EntityCallItemDropPackageBase.h"
#include "EntityDef.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_ItemDropPackageBase::EntityBaseEntityCall_ItemDropPackageBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_ItemDropPackageBase::~EntityBaseEntityCall_ItemDropPackageBase()
{
}



EntityCellEntityCall_ItemDropPackageBase::EntityCellEntityCall_ItemDropPackageBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_ItemDropPackageBase::~EntityCellEntityCall_ItemDropPackageBase()
{
}


}