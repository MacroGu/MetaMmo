#include "EntityCallSceneBase.h"
#include "EntityDef.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_SceneBase::EntityBaseEntityCall_SceneBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_SceneBase::~EntityBaseEntityCall_SceneBase()
{
}



EntityCellEntityCall_SceneBase::EntityCellEntityCall_SceneBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_SceneBase::~EntityCellEntityCall_SceneBase()
{
}


}