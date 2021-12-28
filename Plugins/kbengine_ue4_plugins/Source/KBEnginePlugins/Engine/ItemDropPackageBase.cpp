#include "ItemDropPackageBase.h"
#include "KBVar.h"
#include "EntityDef.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "MemoryStream.h"
#include "EntityComponent.h"

namespace KBEngine
{



void ItemDropPackageBase::onComponentsEnterworld()
{
}

void ItemDropPackageBase::onComponentsLeaveworld()
{
}

void ItemDropPackageBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_ItemDropPackageBase(id(), className());
}

void ItemDropPackageBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_ItemDropPackageBase(id(), className());
}

void ItemDropPackageBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* ItemDropPackageBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* ItemDropPackageBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void ItemDropPackageBase::onRemoteMethodCall(MemoryStream& stream)
{
}

void ItemDropPackageBase::onUpdatePropertys(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("ItemDropPackage");

	while(stream.length() > 0)
	{
		uint16 componentPropertyUType = 0;
		uint16 properUtype = 0;

		if (sm->usePropertyDescrAlias)
		{
			componentPropertyUType = stream.readUint8();
			properUtype = stream.read<uint8>();
		}
		else
		{
			componentPropertyUType = stream.readUint16();
			properUtype = stream.read<uint16>();
		}

		if(componentPropertyUType > 0)
		{
			KBE_ASSERT(false);

			return;
		}

		Property* pProp = sm->idpropertys[properUtype];

		switch(pProp->properUtype)
		{
			case 40001:
			{
				FVector oldval_direction = direction;
				direction = stream.readVector3();

				if(pProp->isBase())
				{
					if(inited())
						onDirectionChanged(oldval_direction);
				}
				else
				{
					if(inWorld())
						onDirectionChanged(oldval_direction);
				}

				break;
			}
			case 55:
			{
				ITEM_LIST oldval_dropItems = dropItems;
				((DATATYPE_ITEM_LIST*)EntityDef::id2datatypes[27])->createFromStreamEx(stream, dropItems);

				if(pProp->isBase())
				{
					if(inited())
						onDropItemsChanged(oldval_dropItems);
				}
				else
				{
					if(inWorld())
						onDropItemsChanged(oldval_dropItems);
				}

				break;
			}
			case 52:
			{
				uint64 oldval_ownerDBID = ownerDBID;
				ownerDBID = stream.readUint64();

				if(pProp->isBase())
				{
					if(inited())
						onOwnerDBIDChanged(oldval_ownerDBID);
				}
				else
				{
					if(inWorld())
						onOwnerDBIDChanged(oldval_ownerDBID);
				}

				break;
			}
			case 40000:
			{
				FVector oldval_position = position;
				position = stream.readVector3();

				if(pProp->isBase())
				{
					if(inited())
						onPositionChanged(oldval_position);
				}
				else
				{
					if(inWorld())
						onPositionChanged(oldval_position);
				}

				break;
			}
			case 40002:
			{
				stream.readUint32();
				break;
			}
			default:
				break;
		};
	}
}

void ItemDropPackageBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs["ItemDropPackage"];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

	FVector oldval_direction = direction;
	Property* pProp_direction = pdatas[2];
	if(pProp_direction->isBase())
	{
		if(inited() && !inWorld())
			onDirectionChanged(oldval_direction);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_direction->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onDirectionChanged(oldval_direction);
			}
		}
	}

	ITEM_LIST oldval_dropItems = dropItems;
	Property* pProp_dropItems = pdatas[4];
	if(pProp_dropItems->isBase())
	{
		if(inited() && !inWorld())
			onDropItemsChanged(oldval_dropItems);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_dropItems->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onDropItemsChanged(oldval_dropItems);
			}
		}
	}

	uint64 oldval_ownerDBID = ownerDBID;
	Property* pProp_ownerDBID = pdatas[5];
	if(pProp_ownerDBID->isBase())
	{
		if(inited() && !inWorld())
			onOwnerDBIDChanged(oldval_ownerDBID);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_ownerDBID->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onOwnerDBIDChanged(oldval_ownerDBID);
			}
		}
	}

	FVector oldval_position = position;
	Property* pProp_position = pdatas[1];
	if(pProp_position->isBase())
	{
		if(inited() && !inWorld())
			onPositionChanged(oldval_position);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_position->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onPositionChanged(oldval_position);
			}
		}
	}

}

ItemDropPackageBase::ItemDropPackageBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL),
	dropItems(),
	ownerDBID((uint64)FCString::Atoi64(TEXT("0")))
{
}

ItemDropPackageBase::~ItemDropPackageBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;

}

void ItemDropPackageBase::attachComponents()
{
}

void ItemDropPackageBase::detachComponents()
{
}

}