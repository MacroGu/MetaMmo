#include "OreBase.h"
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



void OreBase::onComponentsEnterworld()
{
}

void OreBase::onComponentsLeaveworld()
{
}

void OreBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_OreBase(id(), className());
}

void OreBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_OreBase(id(), className());
}

void OreBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* OreBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* OreBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void OreBase::onRemoteMethodCall(MemoryStream& stream)
{
}

void OreBase::onUpdatePropertys(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("Ore");

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
			case 58:
			{
				uint8 oldval_digCount = digCount;
				digCount = stream.readUint8();

				if(pProp->isBase())
				{
					if(inited())
						onDigCountChanged(oldval_digCount);
				}
				else
				{
					if(inWorld())
						onDigCountChanged(oldval_digCount);
				}

				break;
			}
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
			case 57:
			{
				uint32 oldval_oreID = oreID;
				oreID = stream.readUint32();

				if(pProp->isBase())
				{
					if(inited())
						onOreIDChanged(oldval_oreID);
				}
				else
				{
					if(inWorld())
						onOreIDChanged(oldval_oreID);
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

void OreBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs["Ore"];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

	uint8 oldval_digCount = digCount;
	Property* pProp_digCount = pdatas[4];
	if(pProp_digCount->isBase())
	{
		if(inited() && !inWorld())
			onDigCountChanged(oldval_digCount);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_digCount->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onDigCountChanged(oldval_digCount);
			}
		}
	}

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

	uint32 oldval_oreID = oreID;
	Property* pProp_oreID = pdatas[5];
	if(pProp_oreID->isBase())
	{
		if(inited() && !inWorld())
			onOreIDChanged(oldval_oreID);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_oreID->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onOreIDChanged(oldval_oreID);
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

OreBase::OreBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL),
	digCount((uint8)FCString::Atoi64(TEXT("0"))),
	oreID((uint32)FCString::Atoi64(TEXT("0")))
{
}

OreBase::~OreBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;

}

void OreBase::attachComponents()
{
}

void OreBase::detachComponents()
{
}

}